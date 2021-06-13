#include "LeaveHouseState.h"
#include "ChaseState.h"
#include <iostream>

using namespace std;

LeaveHouseState::LeaveHouseState(int startX, int startY, Map* m, HumanPlayer* player, BasicGhost* c) {
	Draw* draw = Draw::instance();
	tileHeight = draw->getTileHeight();
	tileWidth = draw->getTileWidth();
	tileSize = draw->getTileSize();
	width = tileSize * tileWidth;
	height = tileSize * tileHeight;
	speed = tileSize / 10;

	x = startX;
	y = startY;
	map = m;
	target = player;
	dir = UP;
	lastTileX = -1;
	lastTileY = -1;
	context = c;
}

LeaveHouseState::~LeaveHouseState() {
	return;
}

bool LeaveHouseState::update(double pelletPercent) {
	if (map->getMapPos(getTileX(),getTileY()) != 0) return GhostState::update(pelletPercent);
	else changeState(new ChaseState(getTileX() * tileSize + (tileSize / 2), getTileY() * tileSize + (tileSize / 2), map, target, context));
	return true;
}

bool LeaveHouseState::moveUp() {
	y -= speed;
	return true;
}

bool LeaveHouseState::isValidTile(int tileX, int tileY) {
	return true;
}

int LeaveHouseState::choosePath(vector<int> options) {
	if (map->getMapPos(getTileX(), getTileY()) == 2) {
		if (map->getMapPos(getTileX(), getTileY() + 1) == 0) return DOWN;
		else if (map->getMapPos(getTileX(), getTileY() - 1) == 0) return UP;
		else if (map->getMapPos(getTileX() - 1, getTileY()) == 0) return LEFT;
		else return RIGHT;
	}
	else {
		options = vector<int>();
		options.push_back(UP);
		options.push_back(DOWN);
		options.push_back(LEFT);
		options.push_back(RIGHT);

		vector<double> distances = vector<double>();
		int index = 0;
		double min = 1000000000000;

		for (unsigned int i = 0; i < options.size(); i++) {
			switch (options.at(i)) {
			case RIGHT:
				distances.push_back(map->getDistance(getTileX() + 1, getTileY()));
				break;
			case LEFT:
				distances.push_back(map->getDistance(getTileX() - 1, getTileY()));
				break;
			case UP:
				distances.push_back(map->getDistance(getTileX(), getTileY() - 1));
				break;
			case DOWN:
				distances.push_back(map->getDistance(getTileX(), getTileY() + 1));
				break;
			}
		}

		for (unsigned int i = 0; i < distances.size(); i++) {
			if (distances.at(i) < min) {
				min = distances.at(i);
				index = i;
			}
		}

		return options.at(index);
	}
}

void LeaveHouseState::draw(int r, int g, int b) {
	Draw* draw = Draw::instance();
	draw->drawGhost(x, y, dir, r, g, b);
	return;
}