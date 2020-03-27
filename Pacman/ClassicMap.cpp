#include "ClassicMap.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <allegro5/allegro_primitives.h>

const int SQUARE_SIZE = 40;

using namespace std;

ClassicMap::ClassicMap() {
	ifstream mapData("levels/level1.pac");
	pellets = 0.0;
	pelletsEaten = 0.0;

	string line;
	getline(mapData, line);
	istringstream is(line);
	is >> height >> width;

	map = new int*[height];
	object = new int*[height];

	for (int i = 0; i < height; i++) {
		map[i] = new int[width];
		object[i] = new int[width];
	}

	for (int y = 0; y < height; y++) {
		getline(mapData, line);
		istringstream is(line);
		for (int x = 0; x < width; x++) {
			is >> map[y][x];
		}
	}

	for (int y = 0; y < height; y++) {
		getline(mapData, line);
		istringstream is(line);
		for (int x = 0; x < width; x++) {
			is >> object[y][x];
			if (object[y][x] == 1) pellets++;
		}
	}

	frame = 0;

	return;
}

ClassicMap::~ClassicMap() {
	return;
}

int ClassicMap::getMapPos(int x, int y) {
	return map[y][x];
}

int ClassicMap::getObjectPos(int x, int y) {
	return object[y][x];
}

void ClassicMap::eatObject(int x, int y) {
	pelletsEaten++;
	object[y][x] = 0;
}

bool ClassicMap::update() {
	frame = (++frame) % 30;
	return frame % 5 == 0;
}

void ClassicMap::draw() {
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			if (map[y][x] == 1) drawWalls(x, y);
			else if (map[y][x] == 2) al_draw_line(x * SQUARE_SIZE, y * SQUARE_SIZE, (x+1) * SQUARE_SIZE, y * SQUARE_SIZE, al_map_rgb(0, 0, 255), 3);
			
			if (object[y][x] == 1) al_draw_filled_circle(x * SQUARE_SIZE + (SQUARE_SIZE/2), y * SQUARE_SIZE + (SQUARE_SIZE/2), SQUARE_SIZE / 8, al_map_rgb(219, 133, 28));
			if (object[y][x] == 2) {
				if(frame < 15)al_draw_filled_circle(x * SQUARE_SIZE + (SQUARE_SIZE/2), y * SQUARE_SIZE + (SQUARE_SIZE/2), 5 + (frame/5), al_map_rgb(219, 133, 28));
				else al_draw_filled_circle(x * 40 + 20, y * 40 + 20, 7 - ((frame-14) / 5), al_map_rgb(219, 133, 28));
			}
		}
	}
	return;
}

void ClassicMap::drawWalls(int x, int y) {
	float PI = 3.14159265;
	/*if(x == 0 || x == 19 || y == 0 || y == 14) */al_draw_rectangle(x * 40, y * 40, x * 40 + 40, y * 40 + 40, al_map_rgb(0, 255, 255), 1);
	return;
}


void ClassicMap::getHouseCoordinates(int &coordX, int &coordY) {
	coordX = 9;
	coordY = 6;
	return;
}

double ClassicMap::getPelletPercent() {
	return pelletsEaten / pellets;
}