#include <EdgeEngine_library.h>
#include <time.h>

using std::vector;
using std::string;

bool testTemp = false;
clock_t cycleCounter;
clock_t sleepTime;

sample* temperature = NULL;

edgine* Edge;
connection_windows* Connection;
vector<sample*> samples;

float getTemperature(){
  if(testTemp)
    return 24.0F;
  else
    return 24.5F;
}

void setup() {
    // setup connection
    Connection = connection_windows::getInstance();
    options opts;
    //login
    opts.username = "riccardo-office-temperature-sensor-username";
    opts.password =  "riccardo-office-temperature-sensor-password";
    //route
    opts.url = "http://students.atmosphere.tools";
    opts.ver = "v1";
    opts.login = "login";
    opts.devs = "devices";
    opts.scps = "scripts";
    opts.measurements = "measurements";
    opts.info= "info";
    opts.issues="issues";
    //Edgine identifiers
    opts.thing = "riccardo-office";
    opts.device = "environment-riccardo-office";
    opts.id = "environment-riccardo-office";
    //initialize Edge engine
    Edge = edgine::getInstance();
    Edge->init(opts);
}

void action() {
    cycleCounter = clock();

    //create a temperature measurement sample
    temperature = new sample("temperature");
    temperature->startDate = Edge->Api->getActualDate();
    temperature->endDate = temperature->startDate;
    testTemp = !testTemp;
    temperature->value = getTemperature();
    samples.push_back(temperature);

    Edge->evaluate(samples);

    samples.clear(); // after evaluated all samples delete them

    delete temperature;
    temperature = NULL;

    cycleCounter=clock()-cycleCounter;// duration of the execution of the cycle

    // subtract te execution time to the Sleep period if result is not negative
    ((float)cycleCounter/CLOCKS_PER_SEC) < Edge->getPeriod() ? sleepTime = (Edge->getPeriod() - (float)cycleCounter/CLOCKS_PER_SEC)*1000 : sleepTime = 0;//delay in milliseconds
  
    Sleep(sleepTime);
}

int main() {
    setup();
    action();
}