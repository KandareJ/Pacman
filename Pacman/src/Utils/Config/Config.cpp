#include "Config.h"

void Config::addKey(std::string key, std::string value) {
    configMap[key] = value;
}

int Config::getIntegerValue(std::string key) {
    return atoi(getStringValue(key).c_str());
}

std::string Config::getStringValue(std::string key) {
    if (configMap.find(key) == configMap.end()) {
        return "default";
    }
    else return configMap[key];
}
