#include "Config.h"

void Config::addKey(string key, string value) {
    configMap[key] = value;
}

int Config::getIntegerValue(string key) {
    return atoi(getStringValue(key).c_str());
}

string Config::getStringValue(string key) {
    if (configMap.find(key) == configMap.end()) {
        return "default";
    }
    else return configMap[key];
}
