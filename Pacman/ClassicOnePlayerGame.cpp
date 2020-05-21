#include "ClassicOnePlayerGame.h"

ClassicOnePlayerGame::ClassicOnePlayerGame() {
	map = new ClassicMap();
	player = new HumanPlayer(map, 1, 1);
	ghosts = vector<BlinkyGhost*>();
	ghosts.push_back(new BlinkyGhost(map, player));
	return;
}

ClassicOnePlayerGame::~ClassicOnePlayerGame() {
	return;
}

void ClassicOnePlayerGame::draw() {
	al_clear_to_color(al_map_rgb(0, 0, 0));
	Draw::instance()->drawScore(player->getScore());
	map->draw();
	for (unsigned int i = 0; i < ghosts.size(); i++) ghosts.at(i)->draw();
	player->draw();
	al_flip_display();

	return;
}

bool ClassicOnePlayerGame::update() {
	bool drawNeeded = false;

	if (map->update()) drawNeeded = true;
	for (unsigned int i = 0; i < ghosts.size(); i++) {
		if (ghosts.at(i)->update()) drawNeeded = true;
	}
	if (player->update()) drawNeeded = true;

	return drawNeeded;
}

bool ClassicOnePlayerGame::run(ALLEGRO_EVENT events) {
	bool drawNeeded = false;

	if (events.type == ALLEGRO_EVENT_TIMER) {
		drawNeeded = update();
		if (drawNeeded) draw();
	}

	if (events.type == ALLEGRO_EVENT_KEY_DOWN) {
		switch (events.keyboard.keycode) {
		case ALLEGRO_KEY_W:
			player->changeDirection(UP);
			break;
		case ALLEGRO_KEY_A:
			player->changeDirection(LEFT);
			break;
		case ALLEGRO_KEY_S:
			player->changeDirection(DOWN);
			break;
		case ALLEGRO_KEY_D:
			player->changeDirection(RIGHT);
			break;
		case ALLEGRO_KEY_ESCAPE:
			return true;
		}
	}
	return false;
}

HumanPlayer* ClassicOnePlayerGame::getPlayer() {
	return player;
}

Map* ClassicOnePlayerGame::getMap() {
	return map;
}