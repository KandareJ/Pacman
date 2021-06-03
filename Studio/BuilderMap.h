#ifndef BUILDER_MAP_H
#define BUILDER_MAP_H

#include "../Pacman/src/Map/Map.h"
#include "../Pacman/src/Graphics/Draw.h"
#include "../Pacman/src/Map/Coordinate.h"
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string>

enum STATE {MAP, OBJ, SPAWN, CHERRY};

class BuilderMap : public Map {
    public:
	BuilderMap(int w, int h, int options, std::string filename);
	~BuilderMap();
	void draw();
	bool run(ALLEGRO_EVENT events);
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
	void setMap(int val);
	void writeFile();
	void next();
	string filename;
	STATE state;
	int curObj;
	int height;
	double pellets;
	double pelletsEaten;
	int width;
	int **map;
	int **object;
	int **spawns;
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
    int selectX;
    int selectY;
	bool quit;
};

#endif