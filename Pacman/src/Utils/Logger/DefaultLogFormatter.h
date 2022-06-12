#ifndef DEFAULT_LOG_FORMATTER_H
#define DEFAULT_LOG_FORMATTER_H

#include <time.h>
#include <stdio.h>
#include "LogFormatter.h"

class DefaultLogFormatter : public LogFormatter {
public:
    std::string format(std::string level, std::string message);
private:
    std::string getTimestamp();
};

#endif

