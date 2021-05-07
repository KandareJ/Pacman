#ifndef GHOSTSTATE_H
#define GHOSTSTATE_H

#include "../../Map/Map.h"
#include "../../Player/HumanPlayer.h"
#include "../BasicGhost.h"
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <time.h>

class GhostState {
public:
	virtual bool update(double pelletPercent);
	virtual void draw(int r, int g, int b) = 0;
	virtual void frighten();
	virtual void scatter(int targetX, int targetY);
	virtual void chase(HumanPlayer* target);
	int getPosX();
	int getPosY();
	virtual int collision();
	virtual ~GhostState();

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
	virtual bool isValidTile(int tileX, int tileY);
	vector<int> getOptions(int tileX, int tileY);
	BasicGhost* context;
	int height;
	int width;
	int tileHeight;
	int tileWidth;
	int tileSize;
};

#endif