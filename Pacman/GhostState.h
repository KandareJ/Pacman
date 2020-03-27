#ifndef GHOSTSTATE_H
#define GHOSTSTATE_H

#include "Map.h"
#include "HumanPlayer.h"
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <time.h> 


class GhostState {
public:
	virtual bool update();
	virtual void draw();

protected:
	virtual int choosePath(vector<int> options);
	HumanPlayer* target;
	int x;
	int y;
	int lastTileX;
	int lastTileY;
	int dir;
	int speed;
	Map* map;
	bool moveLeft();
	bool moveRight();
	bool moveUp();
	bool moveDown();
	int getTileX();
	int getTileY();
	void snapTileX();
	void snapTileY();
	int getTileOffsetX();
	int getTileOffsetY();
	void changeDirection();
	double getDistance(int tileX, int tileY, int tileX2, int tileY2);
	bool isValidTile(int tileX, int tileY);
	vector<int> getOptions(int tileX, int tileY);
};

#endif