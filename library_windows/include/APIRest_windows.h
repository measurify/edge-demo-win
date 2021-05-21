#ifndef APIRest_windows_h
#define APIRest_windows_h

#define SECOND 1000
// #include <Poco/Net/HTTPResponse.h>
#define POCO_WIN32_UTF8
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Path.h>
#include <Poco/URI.h>
#include <Poco/Exception.h>
#include <Poco/StreamCopier.h>
#include <iostream>
#include "sample.h"
#include <vector>
using std::vector;
#include <string>
using std::string;
#include <time.h>
using std::cout;
using std::ostream;
using std::istream;
using std::endl;
using std::to_string;


typedef struct{
  string device;
  string date;
  string message;
  string type;
  string url;
} issue;

class APIRest_windows
{
private:
    //variables
    bool reposting;
    string response;
    char status [4];
    long startingTime;
    string timestamp;
    bool success;
    vector<sample> sampleBuffer;
    vector<issue> issueBuffer;
    int sampleBufferSize=20;
    int issueBufferSize=20;
    int decimationPolicyFactor = 2; // size/decimationPolicyFactor; that is half of data will be deleted
    float timeElapsed;
    //constructor
    APIRest_windows();
    //variables
    static APIRest_windows* instance;
    //methods
    bool isHTTPCodeOk(int);
    string parseResponse(string,string,bool = true);
    void deleteSpaces(string);
    bool needToBeRePOST(string);
    void checkSampleBufferSize();
    void rePOSTMeasurement(string);
    void checkIssueBufferSize();
    void rePOSTIssue(string);
public:
    //methods
    static APIRest_windows* getInstance();
    string POSTLogin(string, string, string, string);
    string GETInfoUpdateDate(string, string);
    string GETDescr(string,string);
    string GETScript(string,string);
    bool POSTMeasurement(sample,string);
    bool POSTIssue(string,string,string,string,string="generic",string=APIRest_windows::getInstance()->getActualDate());
    string getActualDate();
    int getSampleBufferSize();
    int getIssueBufferSize();
    void setSampleBufferSize(int);
    void setIssueBufferSize(int);
};

#endif