#ifndef FILE_LOGGER_H
#define FILE_LOGGER_H

#include <stdio.h>

#include "Logger.h"
#include "DefaultLogFormatter.h"

class FileLogger : public Logger {
public:
    FileLogger();
    ~FileLogger();
    virtual void debug(std::string message);
    virtual void info(std::string message);
    virtual void warn(std::string message);
    virtual void error(std::string message);
    void setFile(FILE* fd);
protected:
    FILE* file;
    LogFormatter* logFormatter;
    void printLog(std::string level, std::string message);
};

#endif