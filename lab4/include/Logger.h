#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <iostream>
#include <cstdarg>
#include <string>
#include <cstdio>
#include <time.h>
#include <ctime>
using namespace std;

class Logger
{
    public:
        char* file;
        Logger(char*);  //Takes file name as input
        void add(string);
        string currentDateTime(); //Gives current date and time to be logged
};

#endif