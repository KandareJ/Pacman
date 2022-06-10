#ifndef DEFAULT_LOG_FORMATTER_H
#define DEFAULT_LOG_FORMATTER_H

#include <time.h>
#include <stdio.h>
#include "LogFormatter.h"

class DefaultLogFormatter : public LogFormatter {
public:
    string format(string level, string message);
private:
    string getTimestamp();
};

#endif

