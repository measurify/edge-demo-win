#include <EdgeEngine_library.h>
#include <time.h>
#include <windows.h>
#include <tchar.h>

using std::vector;
using std::string;


clock_t cycleCounter;
clock_t sleepTime;
int conversionFactor = 1024*1024*1024;
int loopCount = 1; //number of iterations, to be adjusted

float totalRAM,freeRAM, totalROM, freeROM;

sample* totalRAMSample = NULL;
sample* totalROMSample = NULL;
sample* availableRAMSample = NULL;
sample* availableROMSample = NULL;

edgine* Edge;
connection_windows* Connection;
vector<sample*> samples;

void getRAMinfo(){
    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&memInfo);
    DWORDLONG totalPhysMem = memInfo.ullTotalPhys;
    totalRAM = ((float)(totalPhysMem))/conversionFactor;
    cout << "Total RAM installed: ";
    cout << totalRAM;
    cout << " GB" << endl;
    DWORDLONG physMemUsed = memInfo.ullTotalPhys - memInfo.ullAvailPhys;
    freeRAM = ((float)(physMemUsed))/conversionFactor;
    cout << "Total RAM currently used: ";
    cout << freeRAM;
    cout << " GB" << endl;
}

void getROMinfo(){
    unsigned __int64 i64FreeBytesToCaller, i64TotalBytes, i64FreeBytes;
    GetDiskFreeSpaceExW(NULL, (PULARGE_INTEGER)&i64FreeBytesToCaller, (PULARGE_INTEGER)&i64TotalBytes,
                    (PULARGE_INTEGER)&i64FreeBytes);
    totalROM = ((float)(i64TotalBytes))/conversionFactor;
    cout << "Total space: ";
    cout << totalROM;
    cout << " GB" << endl;
    freeROM = ((float)(i64FreeBytes))/conversionFactor;
    cout << "Free space available: ";
    cout <<  freeROM;
    cout << " GB" << endl;
}

void setup() {
    // setup connection
    Connection = connection_windows::getInstance();
    options opts;
    //login
    opts.username = "pc-sensor-username";
    opts.password =  "pc-sensor-password";
    //route
    opts.url = "https://students.atmosphere.tools";
    opts.ver = "v1";
    opts.login = "login";
    opts.devs = "devices";
    opts.scps = "scripts";
    opts.measurements = "measurements";
    opts.info= "info";
    opts.issues="issues";
    //Edgine identifiers
    opts.thing = "my-pc";
    opts.device = "pc-probe";
    opts.id = "pc-probe";
    //initialize Edge engine
    Edge = edgine::getInstance();
    Edge->init(opts);
}

void action() {
    cycleCounter = clock();

    
    getRAMinfo();
    getROMinfo();

    //create a RAM & ROM measurement sample
    totalRAMSample = new sample("total-ram");
    totalRAMSample->startDate = Edge->Api->getActualDate();
    totalRAMSample->endDate = totalRAMSample->startDate;
    totalRAMSample->value = totalRAM;
    samples.push_back(totalRAMSample);

    availableRAMSample = new sample("available-ram");
    availableRAMSample->startDate = Edge->Api->getActualDate();
    availableRAMSample->endDate = availableRAMSample->startDate;
    availableRAMSample->value = freeRAM;
    samples.push_back(availableRAMSample);

    totalROMSample = new sample("total-rom");
    totalROMSample->startDate = Edge->Api->getActualDate();
    totalROMSample->endDate = totalROMSample->startDate;
    totalROMSample->value = totalROM;
    samples.push_back(totalROMSample);

    availableROMSample = new sample("available-rom");
    availableROMSample->startDate = Edge->Api->getActualDate();
    availableROMSample->endDate = availableROMSample->startDate;
    availableROMSample->value = freeROM;
    samples.push_back(availableROMSample);

    Edge->evaluate(samples);

    samples.clear(); // after evaluated all samples delete them

    delete totalRAMSample; 
    totalRAMSample = NULL;

    delete availableRAMSample;
    availableRAMSample = NULL;

    delete totalROMSample; 
    totalROMSample = NULL;

    delete availableROMSample;
    availableROMSample = NULL;

    cycleCounter=clock()-cycleCounter;// duration of the execution of the cycle

    // subtract te execution time to the Sleep period if result is not negative
    ((float)cycleCounter/CLOCKS_PER_SEC) < Edge->getPeriod() ? sleepTime = (Edge->getPeriod() - (float)cycleCounter/CLOCKS_PER_SEC)*1000 : sleepTime = 0;//delay in milliseconds
  
    Sleep(sleepTime);
}

int main() {
    setup();
    for(int i=0;i<loopCount;i++)
    {
        action();
    }
}