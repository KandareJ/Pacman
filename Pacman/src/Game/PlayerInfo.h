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
        selected = 0;
        nameSelection = 0;
        returned = true;
    }
    
    int r;
    int g;
    int b;
    int selected;
    int score;
    int wins;
    std::string name;
    int nameSelection;
    int colorSelection;
    ALLEGRO_JOYSTICK* joystick;
    bool returned;
};

#endif