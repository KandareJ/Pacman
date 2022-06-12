#ifndef LOGGER_H
#define LOGGER_H

#include <string>

class Logger {
public:
    virtual void debug(std::string message) = 0;
    virtual void info(std::string message) = 0;
    virtual void warn(std::string message) = 0;
    virtual void error(std::string message) = 0;
};

#endif