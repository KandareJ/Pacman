#include "GameSettings.h"
#include "../../Graphics/Audio/Audio.h"
#include "CharacterSelect.h"

const int MAX_NUM_GHOSTS = 20;

GameSettings::GameSettings(GameEngine* c) {
    context = c;
    numGhosts = 4;
    numPlayers = 1;
    selected = 0;
    playmode = 0;
    playmodes.push_back("classic");

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

    draw();
}

GameSettings::~GameSettings() {
    return;
}

bool GameSettings::run(ALLEGRO_EVENT events) {
    if (events.type == ALLEGRO_EVENT_KEY_DOWN) {
		switch (events.keyboard.keycode) {
		case ALLEGRO_KEY_ENTER:
			Audio::instance()->menuSelect();
            settings.numGhosts = numGhosts;
            settings.playmode = playmodes.at(playmode);
            
            for (int i = 0; i < settings.players.size(); i++)
                settings.players.at(i).score = 0;

            for (int i = settings.players.size(); i < numPlayers; i++) {
                PlayerInfo p = PlayerInfo();
                p.nameSelection = 0;
                p.colorSelection = i % 18;
                settings.players.push_back(p);
            }

            context->changeState(new CharacterSelect(context, settings));
			return false;
        case ALLEGRO_KEY_A:
			Audio::instance()->menuMove();
            decrement();
            draw();
            return false;
        case ALLEGRO_KEY_D:
			Audio::instance()->menuMove();
            increment();
            draw();
            return false;
        case ALLEGRO_KEY_S:
			Audio::instance()->menuMove();
            selected = ++selected % 3;
            draw();
            return false;
        case ALLEGRO_KEY_W:
			Audio::instance()->menuMove();
            if (--selected < 0) selected = 2;
            draw();
            return false;
		case ALLEGRO_KEY_ESCAPE:
			return true;
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
}

void GameSettings::increment() {
    if (selected == 1) {
        numGhosts = ++ numGhosts % (MAX_NUM_GHOSTS + 1);
    }
}