#include "BlinkyScatterState.h"
#include "BlinkyChaseState.h"
#include "HumanPlayer.h"
#include <iostream>

BlinkyScatterState::BlinkyScatterState(int startX, int startY, Map* m, HumanPlayer* player, BlinkyGhost* c) {
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
	dir = DOWN;
	lastTileX = -1;
	lastTileY = -1;
	context = c;
}

BlinkyScatterState::~BlinkyScatterState() {
	return;
}

void BlinkyScatterState::draw() {
	Draw* draw = Draw::instance();
	draw->drawGhost(x, y, dir, 255, 0, 0);
	return;
}



int BlinkyScatterState::choosePath(vector<int> options) {
	vector<double> distances = vector<double>();
	int index = 0;
	double min = 1000000000000;

	for (unsigned int i = 0; i < options.size(); i++) {
		switch (options.at(i)) {
		case RIGHT:
			distances.push_back(getDistance(getTileX() + 1, getTileY(), 0, 0));
			break;
		case LEFT:
			distances.push_back(getDistance(getTileX() - 1, getTileY(), 0, 0));
			break;
		case UP:
			distances.push_back(getDistance(getTileX(), getTileY() - 1, 0, 0));
			break;
		case DOWN:
			distances.push_back(getDistance(getTileX(), getTileY() + 1, 0, 0));
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

void BlinkyScatterState::frighten() {
	changeState(new FrightenedState(getTileX(), getTileY(), map, target, context));
}

void BlinkyScatterState::chase() {
	changeState(new BlinkyChaseState(getTileX(), getTileY(), map, target, context));
}