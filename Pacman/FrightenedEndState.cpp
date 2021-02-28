#include "FrightenedEndState.h"
#include "FrightenedState.h"
#include "ReturnHouseState.h"
#include "ChaseState.h"
#include "HumanPlayer.h"
#include <allegro5/allegro_primitives.h>

FrightenedEndState::FrightenedEndState(int startX, int startY, Map* m, HumanPlayer* player, BasicGhost* c) {
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

FrightenedEndState::~FrightenedEndState() {
	return;
}

void FrightenedEndState::draw(int r, int g, int b) {
	Draw* draw = Draw::instance();
    if ((frame / 10) % 2 == 0) draw->drawGhost(x, y, dir, 255, 255, 255);
    else draw->drawGhost(x, y, dir, 0, 0, 255);
	return;
}

int FrightenedEndState::choosePath(vector<int> options) {
	return options.at(rand() % options.size());
}

void FrightenedEndState::frighten() {
	changeState(new FrightenedState(getTileX(), getTileY(), map, target, context));
}

bool FrightenedEndState::update(double pelletPercent) {
	frame++;
	if (frame <= 50) return GhostState::update(pelletPercent);
	else {
		changeState(new ChaseState(getTileX(), getTileY(), map, target, context));
		return true;
	}
}

int FrightenedEndState::collision() {
	changeState(new ReturnHouseState(getTileX(), getTileY(), map, target, context));
	return 1;
}