#include "ClassicOnePlayerGame.h"

ClassicOnePlayerGame::ClassicOnePlayerGame() {
	eq = eq->getInstance();
	map = new ClassicMap();
	player = new HumanPlayer(map, 1, 1);
	ghosts = vector<BlinkyGhost*>();
	ghosts.push_back(new BlinkyGhost(map, player));
	scatterChase = 360;
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
	scatterChase--;
	if (scatterChase == 150) {
		scatter();
	}
	else if (scatterChase == 0) {
		chase();
		scatterChase = 360;
	}

	if (map->update()) drawNeeded = true;
	for (unsigned int i = 0; i < ghosts.size(); i++) {
		if (ghosts.at(i)->update()) drawNeeded = true;
	}
	if (player->update()) drawNeeded = true;

	raiseEvents();

	return drawNeeded;
}

void ClassicOnePlayerGame::raiseEvents() {
	while (!eq->empty()) {
		cout << "Popping event" << endl;
		Event* e = eq->pop();

		switch (e->getType()) {
		case 1:
			frighten();
			break;
		}

		delete e;
	}
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

void ClassicOnePlayerGame::frighten() {
	for (unsigned int i = 0; i < ghosts.size(); i++) {
		ghosts.at(i)->frighten();
	}
}

void ClassicOnePlayerGame::scatter() {
	for (unsigned int i = 0; i < ghosts.size(); i++) {
		ghosts.at(i)->scatter();
	}
}

void ClassicOnePlayerGame::chase() {
	for (unsigned int i = 0; i < ghosts.size(); i++) {
		ghosts.at(i)->chase();
	}
}