#include "ReleaseLogger.h"

ReleaseLogger::ReleaseLogger() {
    FILE* file = fopen(getFileName().c_str(), "a");
    this->setFile(file);
}

ReleaseLogger::~ReleaseLogger() {

}

void ReleaseLogger::debug(string message) {
    return;
}

void ReleaseLogger::info(string message) {
    return;
}

string ReleaseLogger::getFileName() {
    time_t rawtime;
    tm* timeinfo;
    char filename[32];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    sprintf(filename, "%d-%d-%d.log.txt", timeinfo->tm_mon + 1, timeinfo->tm_mday, timeinfo->tm_year + 1900);
    return filename;
}