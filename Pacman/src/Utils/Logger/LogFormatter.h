#ifndef LOG_FORMATTER_H
#define LOG_FORMATTER_H

#include <string>

class LogFormatter {
public:
    virtual std::string format(std::string level, std::string message) = 0;
};

#endif