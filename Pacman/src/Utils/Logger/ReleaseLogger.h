#ifndef RELEASE_LOGGER_H
#define RELEASE_LOGGER_H

#include <time.h>
#include "FileLogger.h"

class ReleaseLogger : public FileLogger {
public:
    ReleaseLogger();
    ~ReleaseLogger();
    void debug(string message);
    void info(string message);
private:
    string getFileName();
};

#endif