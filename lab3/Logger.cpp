#include "Logger.h"

using namespace std;

Logger::Logger(char* f)
{
    file = f;
    freopen(file,"w",stderr);  //stderr will be redirected to file
}

string Logger::currentDateTime()
{
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf,sizeof(buf),"%d-%m-%Y %X",&tstruct);  //Current date and time
    return buf;
}

void Logger::add(string msg)
{
    string dt = currentDateTime();
    cerr << dt << "\t" << msg << "\n";
}
