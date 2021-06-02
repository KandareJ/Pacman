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
	if (map->getMapPos(getTileX(),getTileY()) != 0) return moveUp();
	else changeState(new ChaseState(getTileX() * tileSize + (tileSize / 2), getTileY() * tileSize + (tileSize / 2), map, target, context));
	return true;
}

bool LeaveHouseState::moveUp() {
		y -= speed;
	return true;
}

int LeaveHouseState::choosePath(vector<int> options) {
	return 0;
}

void LeaveHouseState::draw(int r, int g, int b) {
	Draw* draw = Draw::instance();
	draw->drawGhost(x, y, dir, r, g, b);
	return;
}