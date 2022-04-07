#ifndef GAME_INFO_H
#define GAME_INFO_H

#include <vector>
#include <string>
#include "PlayerInfo.h"

class GameInfo {
public:
    GameInfo() {
        numGhosts = 4;
        playmode = "classic";
    }
    ~GameInfo() {
        for (unsigned int i = 0; i < players.size(); i++) {
            delete players.at(i);
        }
    }
    
    int numGhosts;
    std::vector<std::string> levels;
    std::vector<PlayerInfo*> players;
    std::string playmode;

};

#endif