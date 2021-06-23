#include "CharacterSelect.h"
#include "GameSettings.h"
#include "LevelSelect.h"
#include "../../Graphics/Audio/Audio.h"
#include <iostream>

using namespace std;

CharacterSelect::CharacterSelect(GameEngine* c, GameInfo g) {
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

    nameOptions.push_back("jace");
    nameOptions.push_back("cass");
    nameOptions.push_back("jojojo");
    nameOptions.push_back("enema");
    nameOptions.push_back("berto");
    nameOptions.push_back("jewel");
    nameOptions.push_back("miguel");
    nameOptions.push_back("hollan");

    draw();
    return;
}

bool CharacterSelect::run(ALLEGRO_EVENT events) {
    if (events.type == ALLEGRO_EVENT_TIMER) {
        
		ALLEGRO_JOYSTICK_STATE joystick_state;

		for (unsigned int i = 0; i < gameInfo.players.size(); i++) {
			al_get_joystick_state(gameInfo.players.at(i).joystick, &joystick_state);
            
			if (gameInfo.players.at(i).returned && joystick_state.stick[0].axis[0] > 0.95) {
                Audio::instance()->menuMove();
                next(i);
                draw();
                gameInfo.players.at(i).returned = false;
            }
			else if (gameInfo.players.at(i).returned && joystick_state.stick[0].axis[0] < -0.95) {
                Audio::instance()->menuMove();
                prev(i);
                draw();
                gameInfo.players.at(i).returned = false;
            }
			else if (gameInfo.players.at(i).returned && joystick_state.stick[0].axis[1] > 0.95) {
                Audio::instance()->menuMove();
                gameInfo.players.at(i).selected = (gameInfo.players.at(i).selected + 1) % NUM_OPTIONS;
                draw();
                gameInfo.players.at(i).returned = false;
            }
			else if (gameInfo.players.at(i).returned && joystick_state.stick[0].axis[1] < -0.95) {
                Audio::instance()->menuMove();
                gameInfo.players.at(i).selected--;
                if (gameInfo.players.at(i).selected < 0) gameInfo.players.at(i).selected = NUM_OPTIONS - 1;
                draw();
                gameInfo.players.at(i).returned = false;
            }
            else if (joystick_state.stick[0].axis[1] > -0.2 && joystick_state.stick[0].axis[1] < 0.2 && joystick_state.stick[0].axis[0] > -0.2 && joystick_state.stick[0].axis[0] < 0.2) {
                gameInfo.players.at(i).returned = true;
            }
		}
	}

    else if (events.type == ALLEGRO_EVENT_JOYSTICK_BUTTON_DOWN) {
		Audio::instance()->menuSelect();
		switch (events.joystick.button) {
			case 0:
                Audio::instance()->menuSelect();
                offset += 4;
                if (offset >= gameInfo.players.size()) nextScreen();
                break;
			case 1:
                offset -= 4;
                if (offset < 0) context->changeState(new GameSettings(context, gameInfo));
				break;
		}
	}

    return false;
}

void CharacterSelect::next(int playerIndex) {
    if (gameInfo.players.at(playerIndex).selected == 0) {
        gameInfo.players.at(playerIndex).nameSelection = (gameInfo.players.at(playerIndex).nameSelection + 1) % nameOptions.size();
    }
    else if (gameInfo.players.at(playerIndex).selected == 1) {
        gameInfo.players.at(playerIndex).colorSelection = (gameInfo.players.at(playerIndex).colorSelection + 1) % 18;
    }
}

void CharacterSelect::prev(int playerIndex) {
    if (gameInfo.players.at(playerIndex).selected == 0) {
        gameInfo.players.at(playerIndex).nameSelection--;
        if (gameInfo.players.at(playerIndex).nameSelection < 0) gameInfo.players.at(playerIndex).nameSelection = nameOptions.size() - 1;
    }
    else if (gameInfo.players.at(playerIndex).selected == 1) {
        gameInfo.players.at(playerIndex).colorSelection--;
        if (gameInfo.players.at(playerIndex).colorSelection < 0) gameInfo.players.at(playerIndex).colorSelection = 17;
    }
}

void CharacterSelect::draw() {
    Draw* draw = Draw::instance();

	al_clear_to_color(al_map_rgb(0, 0, 0));
    draw->drawCharacterSelect(gameInfo.players, offset, nameOptions);
	al_flip_display();
}

void CharacterSelect::nextScreen() {
    for (unsigned int i = 0; i < gameInfo.players.size(); i++) {
        gameInfo.players.at(i).name = nameOptions.at(gameInfo.players.at(i).nameSelection);
        Draw::instance()->generatePlayerColor(gameInfo.players.at(i).r,
                                              gameInfo.players.at(i).g,
                                              gameInfo.players.at(i).b,
                                              20 * gameInfo.players.at(i).colorSelection);
    }

    context->changeState(new LevelSelect(context, gameInfo));
    return;
}