#ifndef CHARACTER_SELECT_MENU_H
#define CHARACTER_SELECT_MENU_H

#include "Game.h"
#include "../GameInfo.h"
#include "../../Graphics/Draw.h"
#include "../../Drivers/Drivers.h"
#include "../../Utils/Observer.h"
#include <vector>
#include <string>

class CharacterSelectMenu : public Game, public Observer {
public:
    CharacterSelectMenu(GameEngine* c, GameInfo* g);
    ~CharacterSelectMenu();
    bool run(ALLEGRO_EVENT events);
    virtual void observerUpdate(Subject*);

private:
    void draw();
    void nextScreen();
    int offset;
    std::vector<std::string> nameOptions;
    GameInfo* gameInfo;
    GameEngine* context;
};

#endif