#include "ReleaseLogger.h"

ReleaseLogger::ReleaseLogger(std::string filepath) {
    std::string fileName = filepath + getFileName();
    FILE* file = fopen(fileName.c_str(), "a");
    this->setFile(file);
}

ReleaseLogger::~ReleaseLogger() {

}

void ReleaseLogger::debug(std::string message) {
    return;
}

void ReleaseLogger::info(std::string message) {
    return;
}

std::string ReleaseLogger::getFileName() {
    time_t rawtime;
    tm* timeinfo;
    char filename[32];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    sprintf(filename, "%d-%d-%d.log.txt", timeinfo->tm_mon + 1, timeinfo->tm_mday, timeinfo->tm_year + 1900);
    return filename;
}