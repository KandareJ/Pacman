#include "BlinkyLeaveHouseState.h"
#include "BlinkyChaseState.h"
#include <iostream>

using namespace std;

BlinkyLeaveHouseState::BlinkyLeaveHouseState(int startX, int startY, Map* m, HumanPlayer* player, BlinkyGhost* c) {
	Draw* draw = Draw::instance();
	tileHeight = draw->getTileHeight();
	tileWidth = draw->getTileWidth();
	tileSize = draw->getTileSize();
	width = tileSize * tileWidth;
	height = tileSize * tileHeight;
	speed = tileSize / 10;

	x = startX * tileSize + (tileSize / 2);
	y = startY * tileSize + (tileSize / 2);
	map = m;
	target = player;
	dir = UP;
	lastTileX = -1;
	lastTileY = -1;
	context = c;
}

BlinkyLeaveHouseState::~BlinkyLeaveHouseState() {
	return;
}

bool BlinkyLeaveHouseState::update() {
	if (map->getMapPos(getTileX(),getTileY()) != 0) return moveUp();
	else changeState(new BlinkyChaseState(getTileX(), getTileY(), map, target, context));
	return true;
}

bool BlinkyLeaveHouseState::moveUp() {
		y -= speed;
	return true;
}

int BlinkyLeaveHouseState::choosePath(vector<int> options) {
	return 0;
}

void BlinkyLeaveHouseState::draw() {
	Draw* draw = Draw::instance();
	draw->drawGhost(x, y, dir, 255, 0, 0);
	return;
}