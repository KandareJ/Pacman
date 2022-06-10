#ifndef LOGGER_H
#define LOGGER_H

#include <string>

using namespace std;

class Logger {
public:
    virtual void debug(string message) = 0;
    virtual void info(string message) = 0;
    virtual void warn(string message) = 0;
    virtual void error(string message) = 0;
};

#endif