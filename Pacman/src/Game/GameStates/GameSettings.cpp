#include "GameSettings.h"
#include "MainMenu.h"
#include "../../Graphics/Audio/Audio.h"
#include "CharacterSelect.h"
#include <iostream>

using namespace std;

const int MAX_NUM_GHOSTS = 20;

GameSettings::GameSettings(GameEngine* c) {
    numJoysticks = al_get_num_joysticks();
    context = c;
    numGhosts = 4;
    numPlayers = numJoysticks;
    selected = 0;
    playmode = 0;
    playmodes.push_back("classic");
    playmodes.push_back("lms");

    draw();
}

GameSettings::GameSettings(GameEngine* c, GameInfo g) {
    settings = g;
    context = c;
    numGhosts = g.numGhosts;
    numPlayers = g.players.size();
    selected = 0;
    playmode = 0;
    playmodes.push_back("classic");
    playmodes.push_back("lms");

    for (int i = 0; i < playmodes.size(); i++) {
        if (playmodes.at(i).compare(g.playmode) == 0) playmode = i;
    }

    numJoysticks = al_get_num_joysticks();

    draw();
}

GameSettings::~GameSettings() {
    return;
}

bool GameSettings::run(ALLEGRO_EVENT events) {
    if (events.type == ALLEGRO_EVENT_JOYSTICK_BUTTON_DOWN) {
		Audio::instance()->menuSelect();
		switch (events.joystick.button) {
			case 0:
				Audio::instance()->menuSelect();
                if (numPlayers == 0) break;
                settings.numGhosts = numGhosts;
                settings.playmode = playmodes.at(playmode);
                
                for (int i = 0; i < settings.players.size(); i++)
                    settings.players.at(i).score = 0;

                for (int i = settings.players.size(); i < numPlayers; i++) {
                    PlayerInfo p = PlayerInfo();
                    p.nameSelection = 0;
                    p.colorSelection = i % 18;
                    p.joystick = al_get_joystick(i);
                    settings.players.push_back(p);
                }

                context->changeState(new CharacterSelect(context, settings));
                break;
			case 1:
				context->changeState(new MainMenu(context));
				break;
		}
	}

	else if (events.type == ALLEGRO_EVENT_JOYSTICK_AXIS) {
		if (events.joystick.axis == 1 && events.joystick.pos < -0.95) {
			Audio::instance()->menuMove();
            if (--selected < 0) selected = 2;
            draw();
            return false;
		}
		else if (events.joystick.axis == 1 && events.joystick.pos > 0.95) {
			Audio::instance()->menuMove();
            selected = ++selected % 3;
            draw();
            return false;
		}
        else if (events.joystick.axis == 0 && events.joystick.pos < -0.95) {
			Audio::instance()->menuMove();
            decrement();
            draw();
            return false;
		}
		else if (events.joystick.axis == 0 && events.joystick.pos > 0.95) {
			Audio::instance()->menuMove();
            increment();
            draw();
            return false;
		}
	}

    return false;
}

void GameSettings::draw() {
	al_clear_to_color(al_map_rgb(0, 0, 0));
    Draw::instance()->drawSettings(numGhosts, numPlayers, playmodes.at(playmode), selected);
	al_flip_display();

    return;
}

void GameSettings::decrement() {
    if (selected == 1) {
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
        numGhosts = ++ numGhosts % (MAX_NUM_GHOSTS + 1);
    }
    else if (selected == 2) {
        numPlayers = ++numPlayers % numJoysticks + 1;
    }
}