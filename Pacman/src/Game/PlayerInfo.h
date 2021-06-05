#ifndef PLAYER_INFO_H
#define PLAYER_INFO_H

#include <string>

class PlayerInfo {
public:
    PlayerInfo() {
        r = 0;
        g = 0;
        b = 0;
        score = 0;
        wins = 0;
        name = "";
    }
    
    int r;
    int g;
    int b;
    int score;
    int wins;
    std::string name;
};

#endif