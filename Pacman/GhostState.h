#ifndef GHOSTSTATE_H
#define GHOSTSTATE_H

#include "Map.h"
#include "HumanPlayer.h"
#include "BlinkyGhost.h"
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <time.h>

class GhostState {
public:
	virtual bool update();
	virtual void frighten() = 0;
	virtual void draw() = 0;
	virtual void scatter();
	virtual void chase();

protected:
	void changeState(GhostState* s);
	virtual int choosePath(vector<int> options) = 0;
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
	BlinkyGhost* context;
	int height;
	int width;
	int tileHeight;
	int tileWidth;
	int tileSize;
};

#endif