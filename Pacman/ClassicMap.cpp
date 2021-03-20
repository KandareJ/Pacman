#include "ClassicMap.h"
#include <sstream>
#include <fstream>
#include <iostream>

using namespace std;

ClassicMap::ClassicMap(string level) {
	ifstream mapData("levels/" + level + ".pac");
	pellets = 0.0;
	pelletsEaten = 0.0;
	option = -1;
	lastHouseCoord = -1;
	lastSpawnCoord = -1;
	srand(time(NULL));

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
			if (map[y][x] == 3 || map[y][x] == 2) houseCoords.push_back(new Coordinate(x, y));
		}
	}

	getline(mapData, line);
	istringstream is2(line);
	is2 >> numOptions;

	objectOptions = new int**[numOptions];
	for (int i = 0; i < numOptions; i++) {
		objectOptions[i] = new int*[height];
		for (int j = 0; j < height; j++) {
			objectOptions[i][j] = new int[width];
		}
	}

	for (int i = 0; i < numOptions; i++) {
		for (int y = 0; y < height; y++) {
			getline(mapData, line);
			istringstream is(line);
			for (int x = 0; x < width; x++) {
				is >> objectOptions[i][y][x];
			}
		}
	}

	int coords;
	getline(mapData, line);
	istringstream is3(line);
	is3 >> coords;

	for (int i = 0; i < coords; i++) {
		getline(mapData, line);
		istringstream is(line);
		int tempX, tempY;
		is >> tempX >> tempY;
		playerSpawnCoords.push_back(new Coordinate(tempX, tempY));
	}

	getline(mapData, line);
	istringstream is4(line);
	is4 >> coords;

	for (int i = 0; i < coords; i++) {
		getline(mapData, line);
		istringstream is(line);
		int tempX, tempY;
		is >> tempX >> tempY;
		fruitCoords.push_back(new Coordinate(tempX, tempY));
	}

	frame = 0;
	switchObjectMap();
	mapData.close();

	return;
}

ClassicMap::~ClassicMap() {
	for (int i = 0; i < height; i++) {
		delete map[i];
		delete object[i];
	}
	delete map;
	delete object;

	for (int i = 0; i < numOptions; i++) {
		for (int j = 0; j < height; j++) {
			delete objectOptions[i][j];
		}
		delete objectOptions[i];
	}
	delete objectOptions;

	return;
}

int ClassicMap::getMapPos(int x, int y) {
	return map[y][x];
}

int ClassicMap::getObjectPos(int x, int y) {
	return object[y][x];
}

void ClassicMap::eatObject(int x, int y) {
	if (object[y][x] == 1) pelletsEaten++;
	object[y][x] = 0;
}

bool ClassicMap::update() {
	frame = (++frame) % 30;
	if (!fruitOut && getPelletPercent() > .5) {
		int i = rand() % fruitCoords.size();
		object[fruitCoords.at(i)->y][fruitCoords.at(i)->x] = 4;
		fruitOut = true;
	}
	return frame % 5 == 0;
}

void ClassicMap::draw() {
	/* // Uncomment this for party mode.
	// You'll need to uncomment the counter variable in the header file too
	// Also, comment out other al_clear_to_color
	int r, g, b;
	counter = (counter + 1) % 300;
	Draw::generateGhostColor(r, g, b, counter);
	al_clear_to_color(al_map_rgb(r, g, b));*/
	Draw* draw = Draw::instance();
	draw->drawMap(map, object, frame, height, width);
	return;
}

void ClassicMap::getHouseCoordinates(int &coordX, int &coordY) {
	lastHouseCoord = (lastHouseCoord + 1) % houseCoords.size();
	coordX = houseCoords.at(lastHouseCoord)->x;
	coordY = houseCoords.at(lastHouseCoord)->y;
	return;
}

void ClassicMap::getHouseGate(int &coordX, int &coordY) {
	coordX = houseCoords.at(0)->x;
	coordY = houseCoords.at(0)->y;
	return;
}

void ClassicMap::getPlayerSpawnCoordinates(int& x, int& y) {
	lastSpawnCoord = (lastSpawnCoord + 1) % playerSpawnCoords.size();
	x = playerSpawnCoords.at(lastSpawnCoord)->x;
	y = playerSpawnCoords.at(lastSpawnCoord)->y;
	return;
}

double ClassicMap::getPelletPercent() {
	return pelletsEaten / pellets;
}

void ClassicMap::switchObjectMap() {
	fruitOut = false;
	option = (option + 1) % numOptions;
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			object[y][x] = objectOptions[option][y][x];
			if (object[y][x] == 1) pellets++;
		}
	}
}

int ClassicMap::getHeight() {
	return height;
}

int ClassicMap::getWidth() {
	return width;
}