#include "GhostHouseState.h"
#include <iostream>
#include "BlinkyChaseState.h"

using namespace std;

GhostHouseState::GhostHouseState(Map* m, HumanPlayer* player, BlinkyGhost* const c) : context(c) {
	//context = c;
	map = m;
	target = player;
	m->getHouseCoordinates(x, y);
	x = x * 40 + 20;
	y = y * 40 + 20;
	return;
}

GhostHouseState::~GhostHouseState() {
	return;
}

void GhostHouseState::draw() {
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
}

bool GhostHouseState::update() {
	if (map->getPelletPercent() > .1) {
		cout << "changing state" << endl;
		context->changeState(new BlinkyChaseState(1, 1, map, target));
	}
	return false;
}

int GhostHouseState::choosePath(vector<int> options) {
	return -1;
}