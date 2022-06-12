#include "DefaultLogFormatter.h"

std::string DefaultLogFormatter::format(std::string level, std::string message) {
   

    return getTimestamp() + " [" + level + "] " + message;
}

std::string DefaultLogFormatter::getTimestamp() {
    time_t rawtime;
    tm* timeinfo;
    char timestamp[12];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    sprintf(timestamp, "%d:%d:%d", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);

    return timestamp;
}