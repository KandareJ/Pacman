#include "ClassicGame.h"
#include "Scoreboard.h"
#include "../../Graphics/Audio/Audio.h"

ClassicGame::ClassicGame(GameEngine* c, GameInfo* settings) {
	this->settings = settings;
	over = false;
	context = c;
	lastChasePlayer = -1;
	eq = eq->getInstance();
	map = new ClassicMap(settings->levels.at(settings->levels.size() - 1));
	ghosts = std::vector<BasicGhost*>();
	int numGhosts = settings->numGhosts;
	int numPlayers = settings->players.size();
	int r, g, b;
	int hue = (numGhosts) ? 300 / numGhosts : 300;
	int playerHue = 60;
	int playerX, playerY;

	settings->levels.pop_back();

	for (int i = 0; i < numPlayers; i++) {
		map->getPlayerSpawnCoordinates(playerX, playerY);
		players.push_back(new HumanPlayer(map, playerX, playerY, settings->players.at(i)->r, settings->players.at(i)->g, settings->players.at(i)->b, i));
	}

	for (int i = 0; i < numGhosts; i++) {
		Draw::generateGhostColor(r, g, b, hue * i);
		ghosts.push_back(new BasicGhost(map, players.at(0), .5 / (i + 1), r, g, b));
	}

	scatterChase = 360;

	return;
}

ClassicGame::~ClassicGame() {
	for (unsigned int i = 0; i < players.size(); i++) {
		delete players.at(i);
	}

	for (unsigned int i = 0; i < ghosts.size(); i++) {
		delete ghosts.at(i);
	}

	delete map;

	return;
}

void ClassicGame::draw() {
	al_clear_to_color(al_map_rgb(0, 0, 0));
	map->draw();
	for (unsigned int i = 0; i < ghosts.size(); i++) ghosts.at(i)->draw();
	for (unsigned int i = 0; i < players.size(); i++) {
		Draw::instance()->drawScore(players.at(i)->getScore(), i, players.size(), settings->players.at(i));
		players.at(i)->draw();
	}

	al_flip_display();

	return;
}

bool ClassicGame::update() {
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

	int survivors = 0;
	for (unsigned int i = 0; i < players.size(); i++) {
		if (players.at(i)->update()) drawNeeded = true;
		if (players.at(i)->isAlive()) survivors++;
	}

	if (settings->playmode.compare("lms") == 0 && survivors <= 1) over = true;
	else if (survivors <= 0) over = true;

	raiseEvents();
	detectCollisions();

	return drawNeeded;
}

void ClassicGame::raiseEvents() {
	while (!eq->empty()) {
		Event* e = eq->pop();

		switch (e->getType()) {
		case 1:
			frighten();
			break;
		case 2:
			Audio::instance()->eatFruit();
			map->switchObjectMap();
			break;
		}
		
		delete e;
	}
}

bool ClassicGame::run(ALLEGRO_EVENT events) {
	bool drawNeeded = false;

	if (events.type == ALLEGRO_EVENT_TIMER) {
		drawNeeded = update();
		if (drawNeeded) draw();
	}

	else if (events.type == ALLEGRO_EVENT_KEY_DOWN) {
		switch (events.keyboard.keycode) {
		case ALLEGRO_KEY_W:
			players.at(0)->changeDirection(UP);
			break;
		case ALLEGRO_KEY_A:
			players.at(0)->changeDirection(LEFT);
			break;
		case ALLEGRO_KEY_S:
			players.at(0)->changeDirection(DOWN);
			break;
		case ALLEGRO_KEY_D:
			players.at(0)->changeDirection(RIGHT);
			break;
		case ALLEGRO_KEY_ESCAPE:
			return true;
		}
	}

	for (unsigned int i = 0; i < players.size(); i++) {
		settings->players.at(i)->score = players.at(i)->getScore();
	}

	if (over) context->changeState(new Scoreboard(context, settings));

	return false;
}

HumanPlayer* ClassicGame::getPlayer() {
	return players.at(getChasePlayer());
}

Map* ClassicGame::getMap() {
	return map;
}

void ClassicGame::frighten() {
	for (unsigned int i = 0; i < ghosts.size(); i++) {
		ghosts.at(i)->frighten();
	}
}

void ClassicGame::scatter() {
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

void ClassicGame::chase() {
	for (unsigned int i = 0; i < ghosts.size(); i++) {
		ghosts.at(i)->chase(players.at(getChasePlayer()));
	}
}

void ClassicGame::detectCollisions() {
	Draw* draw = Draw::instance();
	double distance = 0.0;
	for (unsigned int i = 0; i < ghosts.size(); i++) {
		for (unsigned int j = 0; j < players.size(); j++) {
			if (players.at(j)->isAlive()) {
				distance = getDistance(players.at(j)->getPosX(), players.at(j)->getPosY(), ghosts.at(i)->getPosX(), ghosts.at(i)->getPosY());
				if (distance <= draw->getTileSize() * .6) {
					players.at(j)->ghostCollision(ghosts.at(i)->collision());
				}
			}
		}
	}
	for (unsigned int i = 0; i < players.size(); i++) {
		for (unsigned int j = i + 1; j < players.size(); j++) {
			distance = getDistance(players.at(i)->getPosX(), players.at(i)->getPosY(), players.at(j)->getPosX(), players.at(j)->getPosY());
			if (distance <= draw->getTileSize() * .6 && players.at(i)->isAlive() && players.at(j)->isAlive()) {
				if (players.at(i)->isBig() && !players.at(j)->isBig()) players.at(j)->die();
				else if (players.at(j)->isBig() && !players.at(i)->isBig()) players.at(i)->die();
			}
		}
	}
}

double ClassicGame::getDistance(int tileX1, int tileY1, int tileX2, int tileY2) {
	return sqrt((tileX1 - tileX2) * (tileX1 - tileX2) + (tileY1 - tileY2) * (tileY1 - tileY2));
}

int ClassicGame::getChasePlayer() {
	std::vector<int> living;

	for (unsigned int i = 0; i < players.size(); i++) {
		if (players.at(i)->isAlive()) living.push_back(i);
	}

	if (living.size() == 0) return 0;
	else {
		lastChasePlayer = ++lastChasePlayer % living.size();
		return living.at(lastChasePlayer);
	}
}