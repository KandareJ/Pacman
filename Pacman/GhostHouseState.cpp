#include "GhostHouseState.h"
#include <iostream>
#include "BlinkyLeaveHouseState.h"

using namespace std;

GhostHouseState::GhostHouseState(Map* m, HumanPlayer* player, BlinkyGhost* c) {
	Draw* draw = Draw::instance();
	tileHeight = draw->getTileHeight();
	tileWidth = draw->getTileWidth();
	tileSize = draw->getTileSize();
	width = tileSize * tileWidth;
	height = tileSize * tileHeight;
	speed = 0;
	context = c;
	map = m;
	target = player;
	dir = UP;
	m->getHouseCoordinates(x, y);
	cout << "house coords: (" << x << ", " << y << ")" << endl;
	x = x * tileSize + (tileSize / 2);
	y = y * tileSize + (tileSize / 2);
	return;
}

GhostHouseState::~GhostHouseState() {
	return;
}

void GhostHouseState::draw() {
	Draw* draw = Draw::instance();
	draw->drawGhost(x, y, dir, 255, 0, 0);
	return;
}

bool GhostHouseState::update() {
	if (map->getPelletPercent() > .1) {
		cout << "changing state" << endl;
		changeState(new BlinkyLeaveHouseState(getTileX(), getTileY(), map, target, context));
		return true;
	}
	return false;
}

int GhostHouseState::choosePath(vector<int> options) {
	return -1;
}