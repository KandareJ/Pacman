#include "ChaseState.h"
#include "ScatterState.h"
#include <allegro5/allegro_primitives.h>
#include <iostream>

ChaseState::ChaseState(int startX, int startY, Map* m, HumanPlayer* player, BasicGhost* c) {
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
	dir = DOWN;
	lastTileX = -1;
	lastTileY = -1;
	context = c;
}

ChaseState::~ChaseState() {
	return;
}

void ChaseState::draw(int r, int g, int b) {
	Draw* draw = Draw::instance();
	draw->drawGhost(x, y, dir, r, g, b);
	return;
}

int ChaseState::choosePath(vector<int> options) {
	vector<double> distances = vector<double>();
	int index = 0;
	double min = 1000000000000;

	for (unsigned int i = 0; i < options.size(); i++) {
		switch (options.at(i)) {
		case RIGHT:
			distances.push_back(getDistance(getTileX()+1, getTileY(), target->getTileX(), target->getTileY()));
			break;
		case LEFT:
			distances.push_back(getDistance(getTileX()-1, getTileY(), target->getTileX(), target->getTileY()));
			break;
		case UP:
			distances.push_back(getDistance(getTileX(), getTileY()-1, target->getTileX(), target->getTileY()));
			break;
		case DOWN:
			distances.push_back(getDistance(getTileX(), getTileY()+1, target->getTileX(), target->getTileY()));
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

void ChaseState::frighten() {
	changeState(new FrightenedState(x, y, map, target, context));
}

void ChaseState::scatter(int targetX, int targetY) {
	changeState(new ScatterState(x, y, map, target, targetX, targetY, context));
}