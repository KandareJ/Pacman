#ifndef LOG_FORMATTER_H
#define LOG_FORMATTER_H

#include <string>

using namespace std;

class LogFormatter {
public:
    virtual string format(string level, string message) = 0;
};

#endif