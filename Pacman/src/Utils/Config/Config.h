#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <map>
#include <stdlib.h>

class Config {
public:
    void addKey(std::string key, std::string value);
    int getIntegerValue(std::string key);
    std::string getStringValue(std::string key);
    void print();
private:
    std::map<std::string, std::string> configMap;
};

#endif