#ifndef STATE_H
#define STATE_H

#include <string>

#include "../Utils/Config/Config.h"
#include "../Utils/Config/ConfigParser.h"
#include "../Utils/Logger/DebugLogger.h"
#include "../Utils/Logger/ReleaseLogger.h"

class State {
public:
    static State* getState();
    Logger* getLogger();
protected:
    State();
private:
    static State* state;
    Logger* logger;
};

#endif