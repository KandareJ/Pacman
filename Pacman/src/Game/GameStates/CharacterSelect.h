#ifndef CHARACTER_SELECT_H
#define CHARACTER_SELECT_H

#include "Game.h"
#include "../GameInfo.h"
#include "../../Graphics/Draw.h"
#include <vector>
#include <string>

const int NUM_OPTIONS = 2;

class CharacterSelect : public Game {
public:
    CharacterSelect(GameEngine* c, GameInfo g);
    bool run(ALLEGRO_EVENT events);

private:
    void draw();
    void next(int playerIndex);
    void prev(int playerIndex);
    void nextScreen();
    int offset;
    std::vector<std::string> nameOptions;
    GameInfo gameInfo;
    GameEngine* context;
};

#endif