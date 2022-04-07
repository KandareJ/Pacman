#include "CharacterSelectMenu.h"
#include "GameSettings.h"
#include "LevelSelect.h"
#include "../../Graphics/Audio/Audio.h"
#include <iostream>

using namespace std;

CharacterSelectMenu::CharacterSelectMenu(GameEngine* c, GameInfo* g) {
    context = c;
    gameInfo = g;
    offset = 0;

    nameOptions.push_back("pac-man");
    nameOptions.push_back("pac-woman");
    nameOptions.push_back("pac-boi");
    nameOptions.push_back("lil' pacc");
    nameOptions.push_back("tu-pac");
    nameOptions.push_back("pac-attac");
    nameOptions.push_back("pac-istan");
    nameOptions.push_back("pac-intosh");
    nameOptions.push_back("pac-rat");
    nameOptions.push_back("ghostbuster");
    nameOptions.push_back("pelletpoppa");
    nameOptions.push_back("pico-man");
    nameOptions.push_back("waka flocka");
    nameOptions.push_back("pac-quiao");
    nameOptions.push_back("hugh janus");

    nameOptions.push_back("jace");
    nameOptions.push_back("cass");
    nameOptions.push_back("jojojo");
    nameOptions.push_back("enema");
    nameOptions.push_back("berto");
    nameOptions.push_back("jewel");
    nameOptions.push_back("miguel");
    nameOptions.push_back("hollan");
    nameOptions.push_back("jared");
    nameOptions.push_back("rachel");

    for (unsigned int i = 0; i < gameInfo->players.size(); i++) {
        gameInfo->players.at(i)->numNames = nameOptions.size();
        Drivers::getDrivers()->getInput()->attach(gameInfo->players.at(i), i);
    }

    Drivers::getDrivers()->getInput()->attachAll(this);

    draw();
    return;
}

CharacterSelectMenu::~CharacterSelectMenu() {
    for (unsigned int i = 0; i < gameInfo->players.size(); i++) {
        gameInfo->players.at(i)->numNames = nameOptions.size();
        Drivers::getDrivers()->getInput()->detach(gameInfo->players.at(i), i);
    }
    Drivers::getDrivers()->getInput()->detachAll(this);
}

void CharacterSelectMenu::observerUpdate(Subject* subject) {
    Joystick* joystick = (Joystick*) subject;
    draw();

    if (joystick->getPreviousButtonPosition(0) == ButtonPosition::DOWN) {
        Audio::instance()->menuSelect();
        offset += 4;
        if (offset >= gameInfo->players.size()) nextScreen();
    }
    else if (joystick->getPreviousButtonPosition(1) == ButtonPosition::DOWN) {
        Audio::instance()->menuSelect();
        offset -= 4;
        if (offset < 0) context->changeState(new GameSettings(context, gameInfo));
    }
}

bool CharacterSelectMenu::run(ALLEGRO_EVENT events) {
    return false;
}

void CharacterSelectMenu::draw() {
    Draw* draw = Draw::instance();

	al_clear_to_color(al_map_rgb(0, 0, 0));
    draw->drawCharacterSelect(gameInfo->players, offset, nameOptions);
	al_flip_display();
}

void CharacterSelectMenu::nextScreen() {
    for (unsigned int i = 0; i < gameInfo->players.size(); i++) {
        gameInfo->players.at(i)->name = nameOptions.at(gameInfo->players.at(i)->nameSelection);
        Draw::instance()->generatePlayerColor(gameInfo->players.at(i)->r,
                                              gameInfo->players.at(i)->g,
                                              gameInfo->players.at(i)->b,
                                              20 * gameInfo->players.at(i)->colorSelection);
    }

    context->changeState(new LevelSelect(context, gameInfo));
    return;
}