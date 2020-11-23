#include "ClassicOnePlayerGame.h"

ClassicOnePlayerGame::ClassicOnePlayerGame() {
	eq = eq->getInstance();
	map = new ClassicMap();
	player = new HumanPlayer(map, 1, 1);
	ghosts = vector<BasicGhost*>();
	int numGhosts = 4;

	for (int i = 0; i < numGhosts; i++) {
		ghosts.push_back(new BasicGhost(map, player, .5 / (i + 1)));
	}

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
	detectCollisions();

	return drawNeeded;
}

void ClassicOnePlayerGame::raiseEvents() {
	while (!eq->empty()) {
		Event* e = eq->pop();

		switch (e->getType()) {
		case 1:
			frighten();
			break;
		case 2:
			map->switchObjectMap();
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
	int h = map->getHeight();
	int w = map->getWidth();
	for (unsigned int i = 0; i < ghosts.size(); i++) {
		switch (i % 4) {
		case 0:
			ghosts.at(i)->scatter(0, 0);
			break;
		case 1:
			ghosts.at(i)->scatter(0, h);
			break;
		case 2:
			ghosts.at(i)->scatter(w, 0);
			break;
		case 3:
			ghosts.at(i)->scatter(w, h);
			break;
		}
	}
}

void ClassicOnePlayerGame::chase() {
	for (unsigned int i = 0; i < ghosts.size(); i++) {
		ghosts.at(i)->chase(player);
	}
}

void ClassicOnePlayerGame::detectCollisions() {
	Draw* draw = Draw::instance();
	double distance = 0.0;
	for (unsigned int i = 0; i < ghosts.size(); i++) {
		distance = getDistance(player->getPosX(), player->getPosY(), ghosts.at(i)->getPosX(), ghosts.at(i)->getPosY());
		if (distance <= draw->getTileSize() * .6) {
			player->ghostCollision(ghosts.at(i)->collision());
		}
	}
}

double ClassicOnePlayerGame::getDistance(int tileX1, int tileY1, int tileX2, int tileY2) {
	return sqrt((tileX1 - tileX2) * (tileX1 - tileX2) + (tileY1 - tileY2) * (tileY1 - tileY2));
}