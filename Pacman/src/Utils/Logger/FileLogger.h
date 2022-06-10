#ifndef FILE_LOGGER_H
#define FILE_LOGGER_H

#include <stdio.h>

#include "Logger.h"
#include "DefaultLogFormatter.h"

class FileLogger : public Logger {
public:
    FileLogger();
    ~FileLogger();
    virtual void debug(string message);
    virtual void info(string message);
    virtual void warn(string message);
    virtual void error(string message);
    void setFile(FILE* fd);
protected:
    FILE* file;
    LogFormatter* logFormatter;
    void printLog(string level, string message);
};

#endif