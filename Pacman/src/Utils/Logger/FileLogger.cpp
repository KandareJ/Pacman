#include "FileLogger.h"

FileLogger::FileLogger() {
    logFormatter = new DefaultLogFormatter();
}

FileLogger::~FileLogger() {
    delete logFormatter;
}

void FileLogger::setFile(FILE* file) {
    this->file = file;
}

void FileLogger::debug(std::string message) {
    printLog("DEBUG", message);
    return;
}

void FileLogger::info(std::string message) {
    printLog("INFO", message);
    return;
}

void FileLogger::warn(std::string message) {
    printLog("WARN", message);
    return;
}

void FileLogger::error(std::string message) {
    printLog("ERROR", message);
    return;
}

void FileLogger::printLog(std::string level, std::string message) {
    if (file != NULL) {
        fprintf(file, "%s\n", logFormatter->format(level, message).c_str());
        fflush(file);
    }

    return;
}