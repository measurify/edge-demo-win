# Edge Demo Windows
### Table of contents
- [Overview](https://github.com/measurify/edge-demo-win#overview)
- [How to use](https://github.com/measurify/edge-demo-win#how-to-use)
- [Code](https://github.com/measurify/edge-demo-win#code)

## Overview
This demo is based on [edge](https://github.com/Measurify/edge), a generic runtime system capable of processing data flows collected by sensors attached to a device through scripts.
## How to use
=======
##Overview
This demo is based on [edge](https://github.com/Measurify/edge), a generic runtime system capable of processing data flows collected by sensors attached to a device through scripts.
##How to use
>>>>>>> c199cd30b674de52092a02aa7cb9da1cd96d728b
This library requirements are listed on the [edge guide](https://github.com/Measurify/edge#windows). After you ensured your system satisfies all the prerequisites you can start using this demo.
Here you have a sample compile command:
```
-g
main.cpp
-o
main.exe
-Ipath\to\repository\library_windows\include"
-Ipath\to\msys64\mingw64\include
-Lpath\to\repository\library_windows\lib"
-Lpath\to\msys64\mingw64\lib"
-lEdgine"
-lPocoFoundation"
-lPocoUtil"
-lPocoNet" 
``` 
## Code
The example taken into consideration is based on Windows machines and it retrieves data from the computer in use.
Four features are fetched:
- **Total RAM installed**
- **RAM currently available**
- **Total ROM installed**
- **ROM currently available**
The functions used to collect these data are _getRAMinfo()_ and _getROMinfo()_:
```
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
```

```
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
```
Once all the four features are found, data are sent to Measurify: a cloud-based, measurement-oriented platform created by the Elios Lab of the University of Genoa to manage intelligent objects in IoT ecosystems.
