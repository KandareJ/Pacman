#include "GameSettings.h"
#include "../../Graphics/Audio/Audio.h"
#include "LevelSelect.h"

const int MAX_NUM_GHOSTS = 20;

GameSettings::GameSettings(GameEngine* c) {
    context = c;
    numGhosts = 4;
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
            context->changeState(new LevelSelect(context, settings));
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
        case ALLEGRO_KEY_W:
			Audio::instance()->menuMove();
            selected = (selected == 0) ? 1 : 0;
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
    Draw::instance()->drawSettings(numGhosts, playmodes.at(playmode), selected);
	al_flip_display();

    return;
}

void GameSettings::decrement() {
    if (selected == 0) {
        if (--numGhosts < 0) numGhosts = MAX_NUM_GHOSTS;
    }
}

void GameSettings::increment() {
    if (selected == 0) {
        numGhosts = ++ numGhosts % (MAX_NUM_GHOSTS + 1);
    }
}