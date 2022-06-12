#include "GameSettings.h"
#include "MainMenu.h"
#include "../../Graphics/Audio/Audio.h"
#include "CharacterSelectMenu.h"

const int MAX_NUM_GHOSTS = 20;

GameSettings::GameSettings(GameEngine* c) {
    settings = new GameInfo();
    numJoysticks = Drivers::getDrivers()->getInput()->getInputDevicesSize();
    context = c;
    numGhosts = 4;
    numPlayers = numJoysticks;
    selected = 0;
    playmode = 0;
    playmodes.push_back("classic");
    playmodes.push_back("lms");
    Drivers::getDrivers()->getInput()->attachAll(this);

    draw();
}

GameSettings::GameSettings(GameEngine* c, GameInfo* g) {
    settings = g;
    context = c;
    numGhosts = g->numGhosts;
    numPlayers = g->players.size();
    selected = 0;
    playmode = 0;
    playmodes.push_back("classic");
    playmodes.push_back("lms");
    Drivers::getDrivers()->getInput()->attachAll(this);

    for (int i = 0; i < playmodes.size(); i++) {
        if (playmodes.at(i).compare(g->playmode) == 0) playmode = i;
    }

    numJoysticks = Drivers::getDrivers()->getInput()->getInputDevicesSize();
    draw();
}

GameSettings::~GameSettings() {
    Drivers::getDrivers()->getInput()->detachAll(this);
    return;
}

void GameSettings::observerUpdate(Subject* subject) {
    Joystick* joystick = (Joystick*) subject;

    if (joystick->getPreviousButtonPosition(0) == ButtonPosition::DOWN) {
        Audio::instance()->menuSelect();
        if (numPlayers == 0) return;
        settings->numGhosts = numGhosts;
        settings->playmode = playmodes.at(playmode);
        
        for (int i = 0; i < settings->players.size(); i++)
            settings->players.at(i)->score = 0;

        for (int i = settings->players.size(); i < numPlayers; i++) {
            PlayerInfo* p = new PlayerInfo();
            p->nameSelection = 0;
            p->colorSelection = i % 18;
            p->joystick = al_get_joystick(i);
            settings->players.push_back(p);
        }

        context->changeState(new CharacterSelectMenu(context, settings));
    }

    else if (joystick->getPreviousButtonPosition(1) == ButtonPosition::DOWN) {
        Audio::instance()->menuSelect();
        context->changeState(new MainMenu(context));
    }

    else {
        switch (joystick->getPreviousJoystickPosition()) {
        case JoystickPosition::UP:
            Audio::instance()->menuMove();
            if (--selected < 0) selected = 2;
            draw();
            break;
        case JoystickPosition::DOWN:
            Audio::instance()->menuMove();
            selected = ++selected % 3;
            draw();
            break;
        case JoystickPosition::RIGHT:
            Audio::instance()->menuMove();
            increment();
            draw();
            break;
        case JoystickPosition::LEFT:
            Audio::instance()->menuMove();
            decrement();
            draw();
            break;
        };
    }
}

bool GameSettings::run(ALLEGRO_EVENT events) {
    return false;
}

void GameSettings::draw() {
	al_clear_to_color(al_map_rgb(0, 0, 0));
    Draw::instance()->drawSettings(numGhosts, numPlayers, playmodes.at(playmode), selected);
	al_flip_display();

    return;
}

void GameSettings::decrement() {
    if (selected == 0) {
        if (--playmode < 0) playmode = playmodes.size() - 1;
    }
    else if (selected == 1) {
        if (--numGhosts < 0) numGhosts = MAX_NUM_GHOSTS;
    }
    else if (selected == 2) {
        if (--numPlayers < 1) numPlayers = numJoysticks;
    }
}

void GameSettings::increment() {
    if (selected == 0) {
        playmode = ++playmode % playmodes.size();
    }
    else if (selected == 1) {
        numGhosts = ++numGhosts % (MAX_NUM_GHOSTS + 1);
    }
    else if (selected == 2) {
        numPlayers = ++numPlayers % (numJoysticks + 1);
    }
}