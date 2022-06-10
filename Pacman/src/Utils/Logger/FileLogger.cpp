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

void FileLogger::debug(string message) {
    printLog("DEBUG", message);
    return;
}

void FileLogger::info(string message) {
    printLog("INFO", message);
    return;
}

void FileLogger::warn(string message) {
    printLog("WARN", message);
    return;
}

void FileLogger::error(string message) {
    printLog("ERROR", message);
    return;
}

void FileLogger::printLog(string level, string message) {
    if (file != NULL) {
        fprintf(file, "%s\n", logFormatter->format(level, message).c_str());
    }

    return;
}