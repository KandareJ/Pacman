#ifndef MAP_H
#define MAP_H

#include <string>

using namespace std;

class Map {
public:
	virtual void draw() = 0;
	virtual bool update() = 0;
	virtual int getMapPos(int x, int y) = 0;
	virtual int getObjectPos(int x, int y) = 0;
	virtual void eatObject(int x, int y) = 0;
	virtual void getHouseCoordinates(int &x, int &y) = 0;
	virtual double getPelletPercent() = 0;
	virtual void switchObjectMap() = 0;
	virtual int getHeight() = 0;
	virtual int getWidth() = 0;
	virtual int getDistance(int x, int y);
	virtual void getPlayerSpawnCoordinates(int& x, int& y) = 0;
	virtual void getHouseGate(int &x, int &y) = 0;
	virtual ~Map() = 0;
};

#endif