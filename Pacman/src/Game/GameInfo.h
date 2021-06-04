#ifndef GAME_INFO_H
#define GAME_INFO_H

#include <vector>
#include <string>

class GameInfo {
public:
    GameInfo() {
        numGhosts = 4;
        playmode = "classic";
    }
    
    int numGhosts;
    std::vector<std::string> levels;
    std::string playmode;

};

#endif