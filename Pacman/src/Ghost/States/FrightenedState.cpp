#include "FrightenedState.h"
#include "ReturnHouseState.h"
#include "FrightenedEndState.h"
#include <allegro5/allegro_primitives.h>
#include <iostream>

FrightenedState::FrightenedState(int startX, int startY, Map* m, HumanPlayer* player, BasicGhost* c) {
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
	context = c;
	frame = 0;
}

FrightenedState::~FrightenedState() {
	return;
}

void FrightenedState::draw(int r, int g, int b) {
	Draw* draw = Draw::instance();
	draw->drawGhost(x, y, dir, 0, 0, 255);
	return;
}

int FrightenedState::choosePath(vector<int> options) {
	return options.at(rand() % options.size());
}

void FrightenedState::frighten() {
	frame = 0;
}

bool FrightenedState::update(double pelletPercent) {
	frame++;
	if (frame <= 300) return GhostState::update(pelletPercent);
	else {
		changeState(new FrightenedEndState(getTileX(), getTileY(), map, target, context));
		return true;
	}
}

int FrightenedState::collision() {
	changeState(new ReturnHouseState(getTileX(), getTileY(), map, target, context));
	return 1;
}