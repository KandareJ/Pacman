#include "FrightenedState.h"
#include "HumanPlayer.h"
#include <allegro5/allegro_primitives.h>
#include <iostream>

FrightenedState::FrightenedState(int startX, int startY, Map* m, HumanPlayer* player) {
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
	srand(time(NULL));
}

FrightenedState::~FrightenedState() {
	return;
}

void FrightenedState::draw() {
	Draw* draw = Draw::instance();
	draw->drawGhost(x, y, dir, 0, 0, 255);
	return;
}

int FrightenedState::choosePath(vector<int> options) {
	return options.at(rand() % options.size());
}