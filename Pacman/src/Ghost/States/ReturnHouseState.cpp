#include "ReturnHouseState.h"

ReturnHouseState::ReturnHouseState(int x, int y, Map* map, HumanPlayer* player, BasicGhost* c) {
	Draw* draw = Draw::instance();
	tileHeight = draw->getTileHeight();
	tileWidth = draw->getTileWidth();
	tileSize = draw->getTileSize();
	width = tileSize * tileWidth;
	height = tileSize * tileHeight;
	speed = tileSize / 5;

	this->x = x * tileSize + (tileSize / 2);
	this->y = y * tileSize + (tileSize / 2);
	this->map = map;
	target = player;
	dir = UP;
	lastTileX = -1;
	lastTileY = -1;
	context = c;
	map->getHouseGate(targetX, targetY);
}

ReturnHouseState::~ReturnHouseState() {

}

void ReturnHouseState::draw(int r, int g, int b) {
	Draw* draw = Draw::instance();
	draw->drawGhost(x, y, dir, 0, 0, 0);
}


bool ReturnHouseState::update(double pelletPercent) {
	if (getTileX() == targetX && getTileY() == targetY) changeState(new GhostHouseState(map, target, context));
	return GhostState::update(pelletPercent);
}


bool ReturnHouseState::isValidTile(int tileX, int tileY) {
	int tile = map->getMapPos((tileWidth + tileX % tileWidth) % tileWidth, (tileHeight + tileY % tileHeight) % tileHeight);
	return (tile == 0 || tile == 2 || tile == 3);
}

int ReturnHouseState::choosePath(vector<int> options) {
	vector<double> distances = vector<double>();
	int index = 0;
	double min = 1000000000000;

	for (unsigned int i = 0; i < options.size(); i++) {
		switch (options.at(i)) {
		case RIGHT:
			distances.push_back(getDistance(getTileX() + 1, getTileY(), targetX, targetY));
			break;
		case LEFT:
			distances.push_back(getDistance(getTileX() - 1, getTileY(), targetX, targetY));
			break;
		case UP:
			distances.push_back(getDistance(getTileX(), getTileY() - 1, targetX, targetY));
			break;
		case DOWN:
			distances.push_back(getDistance(getTileX(), getTileY() + 1, targetX, targetY));
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

int ReturnHouseState::collision() {
	return 2;
}