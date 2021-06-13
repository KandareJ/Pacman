#include "CharacterSelect.h"
#include "LevelSelect.h"
#include "../../Graphics/Audio/Audio.h"

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

    if (events.type == ALLEGRO_EVENT_KEY_DOWN) {
		switch (events.keyboard.keycode) {
        case ALLEGRO_KEY_W:
            Audio::instance()->menuMove();
            gameInfo.players.at(0).selected--;
            if (gameInfo.players.at(0).selected < 0) gameInfo.players.at(0).selected = NUM_OPTIONS - 1;
            draw();
            break;
        case ALLEGRO_KEY_S:
            Audio::instance()->menuMove();
            gameInfo.players.at(0).selected = (gameInfo.players.at(0).selected + 1) % NUM_OPTIONS;
            draw();
            break;
        case ALLEGRO_KEY_D:
            Audio::instance()->menuMove();
            next(0);
            draw();
            break;
        case ALLEGRO_KEY_A:
            Audio::instance()->menuMove();
            prev(0);
            draw();
            break;
        case ALLEGRO_KEY_ENTER:
            Audio::instance()->menuSelect();
            nextScreen();
            break;
		case ALLEGRO_KEY_ESCAPE:
			return true;
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