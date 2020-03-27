#include "FrightenedState.h"
#include "HumanPlayer.h"
#include <allegro5/allegro_primitives.h>
#include <iostream>

FrightenedState::FrightenedState(int startX, int startY, Map* m, HumanPlayer* player) {
	x = startX * 40 + 20;
	y = startY * 40 + 20;
	map = m;
	target = player;
	dir = DOWN;
	speed = 4;
	lastTileX = -1;
	lastTileY = -1;
	srand(time(NULL));
}

FrightenedState::~FrightenedState() {
	return;
}

void FrightenedState::draw() {
	al_draw_filled_rectangle(x - 10, y - 15, x + 10, y + 15, al_map_rgb(0, 0, 255));
	return;
}

int FrightenedState::choosePath(vector<int> options) {

	return options.at(rand() % options.size());
}