#include "GhostHouseState.h"
#include <iostream>
#include "LeaveHouseState.h"

using namespace std;

GhostHouseState::GhostHouseState(Map* m, HumanPlayer* player, BasicGhost* c) {
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
	x = x * tileSize + (tileSize / 2);
	y = y * tileSize + (tileSize / 2);
	time = 0;
	return;
}

GhostHouseState::~GhostHouseState() {
	return;
}

void GhostHouseState::draw(int r, int g, int b) {
	Draw* draw = Draw::instance();
	draw->drawGhost(x, y, dir, r, g, b);
	return;
}

bool GhostHouseState::update(double pelletPercent) {
	time++;
	if (time > 60 && map->getPelletPercent() > pelletPercent) {
		changeState(new LeaveHouseState(getTileX(), getTileY(), map, target, context));
		return true;
	}
	return false;
}

int GhostHouseState::choosePath(vector<int> options) {
	return -1;
}

void GhostHouseState::frighten() {

}