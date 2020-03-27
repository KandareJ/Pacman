#include "BlinkyScatterState.h"
#include "HumanPlayer.h"
#include <allegro5/allegro_primitives.h>
#include <iostream>

BlinkyScatterState::BlinkyScatterState(int startX, int startY, Map* m, HumanPlayer* player) {
	x = startX * 40 + 20;
	y = startY * 40 + 20;
	map = m;
	target = player;
	dir = DOWN;
	speed = 4;
	lastTileX = -1;
	lastTileY = -1;
}

BlinkyScatterState::~BlinkyScatterState() {
	return;
}

void BlinkyScatterState::draw() {
	al_draw_filled_circle(x, y - 6, 12, al_map_rgb(255, 0, 0));
	al_draw_filled_rectangle(x - 12, y - 6, x + 12, y + 12, al_map_rgb(255, 0, 0));
	al_draw_filled_triangle(x - 12, y + 12, x - 6, y + 12, x - 9, y + 15, al_map_rgb(255, 0, 0));
	al_draw_filled_triangle(x - 6, y + 12, x, y + 12, x - 3, y + 15, al_map_rgb(255, 0, 0));
	al_draw_filled_triangle(x, y + 12, x + 6, y + 12, x + 3, y + 15, al_map_rgb(255, 0, 0));
	al_draw_filled_triangle(x + 12, y + 12, x + 6, y + 12, x + 9, y + 15, al_map_rgb(255, 0, 0));
	al_draw_filled_circle(x - 6, y - 6, 4, al_map_rgb(255, 255, 255));
	al_draw_filled_circle(x + 6, y - 6, 4, al_map_rgb(255, 255, 255));

	switch (dir) {
	case UP:
		al_draw_filled_circle(x - 6, y - 8, 2, al_map_rgb(0, 0, 255));
		al_draw_filled_circle(x + 6, y - 8, 2, al_map_rgb(0, 0, 255));
		break;
	case DOWN:
		al_draw_filled_circle(x - 6, y - 4, 2, al_map_rgb(0, 0, 255));
		al_draw_filled_circle(x + 6, y - 4, 2, al_map_rgb(0, 0, 255));
		break;
	case RIGHT:
		al_draw_filled_circle(x - 4, y - 6, 2, al_map_rgb(0, 0, 255));
		al_draw_filled_circle(x + 8, y - 6, 2, al_map_rgb(0, 0, 255));
		break;
	case LEFT:
		al_draw_filled_circle(x - 8, y - 6, 2, al_map_rgb(0, 0, 255));
		al_draw_filled_circle(x + 4, y - 6, 2, al_map_rgb(0, 0, 255));
		break;
	default:
		al_draw_filled_circle(x - 6, y - 6, 2, al_map_rgb(0, 0, 255));
		al_draw_filled_circle(x + 6, y - 6, 2, al_map_rgb(0, 0, 255));
	};


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