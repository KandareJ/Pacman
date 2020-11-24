#ifndef CLASSICMAP_H
#define CLASSICMAP_H

#include "Map.h"
#include "Draw.h"
#include "ClassicOnePlayerGame.h"
#include "Coordinate.h"
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <time.h>

class ClassicMap : public Map {
public:
	ClassicMap();
	~ClassicMap();
	void draw();
	bool update();
	int getMapPos(int x, int y);
	int getObjectPos(int x, int y);
	void eatObject(int x, int y);
	void getHouseCoordinates(int &x, int &y);
	void getHouseGate(int &x, int &y);
	void getPlayerSpawnCoordinates(int& x, int& y);
	double getPelletPercent();
	void switchObjectMap();
	int getHeight();
	int getWidth();

private:
	int height;
	double pellets;
	double pelletsEaten;
	int width;
	int **map;
	int **object;
	int ***objectOptions;
	std::vector<Coordinate*> fruitCoords;
	std::vector<Coordinate*> houseCoords;
	std::vector<Coordinate*> playerSpawnCoords;
	int lastSpawnCoord;
	int lastHouseCoord;
	int numOptions;
	int option;
	int frame;
	bool fruitOut;
};

#endif