#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "Map.h"

enum DIRECTION { RIGHT, DOWN, LEFT, UP, NOT_MOVING };

class HumanPlayer {
public:
	HumanPlayer(Map* m, int startX, int startY);
	~HumanPlayer();
	bool update();
	void draw();
	void changeDirection(int newDirection);
	int getTileX();
	int getTileY();

private:
	int state;
	int frame;
	int score;
	int x;
	int y;
	int dir;
	int speed;
	Map* map;
	bool moveLeft();
	bool moveRight();
	bool moveUp();
	bool moveDown();
	void snapTileX();
	void snapTileY();
	int getTileOffsetX();
	int getTileOffsetY();
};

#endif