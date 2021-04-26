#include "ScatterState.h"
#include "ChaseState.h"
#include <iostream>

ScatterState::ScatterState(int startX, int startY, Map* m, HumanPlayer* target, int targetX, int targetY, BasicGhost* c) {
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
	this->targetX = targetX;
	this->targetY = targetY;
	dir = DOWN;
	lastTileX = -1;
	lastTileY = -1;
	context = c;
	this->target = target;
}

ScatterState::~ScatterState() {
	return;
}

void ScatterState::draw(int r, int g, int b) {
	Draw* draw = Draw::instance();
	draw->drawGhost(x, y, dir, r, g, b);
	return;
}

int ScatterState::choosePath(vector<int> options) {
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

void ScatterState::frighten() {
	changeState(new FrightenedState(getTileX(), getTileY(), map, target, context));
}

void ScatterState::chase(HumanPlayer* target) {
	changeState(new ChaseState(getTileX(), getTileY(), map, target, context));
}