#include "ClassicMap.h"
#include <sstream>
#include <fstream>
#include <iostream>

using namespace std;

ClassicMap::ClassicMap() {
	ifstream mapData("levels/level1.pac");
	pellets = 0.0;
	pelletsEaten = 0.0;

	string line;
	getline(mapData, line);
	istringstream is(line);
	is >> height >> width;
	Draw::instance()->initializeMapProportions(width, height);

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
	Draw* draw = Draw::instance();
	draw->drawMap(map, object, frame, height, width);
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