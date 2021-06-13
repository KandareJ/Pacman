#ifndef GAME_SETTINGS_H
#define GAME_SETTINGS_H

#include "Game.h"
#include "../../Graphics/Draw.h"
#include <allegro5/allegro.h>
#include "../GameInfo.h"
#include <string>
#include <vector>

class GameSettings : public Game {
public:
    GameSettings(GameEngine* c);
    GameSettings(GameEngine* c, GameInfo g);
    ~GameSettings();
    bool run(ALLEGRO_EVENT events);

private:
    void draw();
    void decrement();
    void increment();
    int numGhosts;
    int numPlayers;
    int playmode;
    int selected;
    std::vector<std::string> playmodes;
	GameEngine* context;
    GameInfo settings;
};

#endif