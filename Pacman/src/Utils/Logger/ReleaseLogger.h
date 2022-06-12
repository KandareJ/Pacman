#ifndef RELEASE_LOGGER_H
#define RELEASE_LOGGER_H

#include <time.h>
#include "FileLogger.h"

class ReleaseLogger : public FileLogger {
public:
    ReleaseLogger(std::string filepath);
    ~ReleaseLogger();
    void debug(std::string message);
    void info(std::string message);
private:
    std::string getFileName();
};

#endif