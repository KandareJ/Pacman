#include "State.h"

State* State::state = 0;

State* State::getState() {
    if (state == 0) {
        state = new State();
    }

    return state;
}

State::State() {
    std::string configValue;
    ConfigParser configParser;
    Config config = configParser.parse("./config");

    configValue = config.getStringValue("log-path");
    
    if (configValue == "default") {
        logger = new DebugLogger();
    }
    else {
        logger = new ReleaseLogger(configValue);
    }
}

Logger* State::getLogger() {
    return logger;
}

