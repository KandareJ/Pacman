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
    
    int numGhosts;
    int numPlayers;
    std::vector<std::string> levels;
    std::vector<PlayerInfo> players;
    std::string playmode;

};

#endif