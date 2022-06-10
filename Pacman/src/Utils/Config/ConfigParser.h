#ifndef CONFIG_PARSER_H
#define CONFIG_PARSER_H

#include <fstream>
#include <sstream>
#include <algorithm>
#include "Config.h"

class ConfigParser {
public:
    Config parse(string path);
private:
    void parseLine(string line);
    string stripWhitespace(string line);
    bool isComment(string line);
    bool isValid(string line);
    Config config;
};

#endif