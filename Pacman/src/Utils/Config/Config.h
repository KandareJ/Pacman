#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <map>
#include <stdlib.h>

using namespace std;

class Config {
public:
    void addKey(string key, string value);
    int getIntegerValue(string key);
    string getStringValue(string key);
    void print();
private:
    map<string, string> configMap;
};

#endif