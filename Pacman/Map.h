#ifndef MAP_H
#define MAP_H

#include <string>

using namespace std;

class Map {
public:
	Map();
	virtual ~Map();
	virtual void draw();
	virtual bool update();
	virtual int getMapPos(int x, int y);
	virtual int getObjectPos(int x, int y);
	virtual void eatObject(int x, int y);
	virtual void getHouseCoordinates(int &x, int &y);
	virtual double getPelletPercent() = 0;
};

#endif