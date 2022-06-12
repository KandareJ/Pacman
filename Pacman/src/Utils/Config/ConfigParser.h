#ifndef CONFIG_PARSER_H
#define CONFIG_PARSER_H

#include <fstream>
#include <sstream>
#include <algorithm>
#include "Config.h"

class ConfigParser {
public:
    Config parse(std::string path);
    //Config parse(const char* path);
private:
    void parseLine(std::string line);
    std::string stripWhitespace(std::string line);
    bool isComment(std::string line);
    bool isValid(std::string line);
    Config config;
};

#endif