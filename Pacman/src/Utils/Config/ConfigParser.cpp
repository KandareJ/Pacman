#include "ConfigParser.h"

Config ConfigParser::parse(std::string path) {
    config = Config();
    std::ifstream configFile(path.c_str());

    std::string line;

    while (getline(configFile, line)) {
        parseLine(line);
    }

    configFile.close();

    return config;
}

void ConfigParser::parseLine(std::string line) {
    std::string strippedLine = stripWhitespace(line);

    if (!isComment(strippedLine)) {
        int index = strippedLine.find('=');
        if (index > 0 && index < strippedLine.length() - 1) {
            config.addKey(strippedLine.substr(0, index), strippedLine.substr(index + 1));
        }
    }
}

std::string ConfigParser::stripWhitespace(std::string line) {
    line.erase(remove(line.begin(), line.end(), ' '), line.end());
    line.erase(remove(line.begin(), line.end(), '\r'), line.end());
    line.erase(remove(line.begin(), line.end(), '\t'), line.end());
    return line;
}

bool ConfigParser::isComment(std::string line) {
    return line.size() > 0 && line.at(0) == '#';
}