#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "../Map/Map.h"
#include "../Graphics/Draw.h"
#include "../Events/EventQueue.h"
#include "../Utils/Observer.h"
#include "../Drivers/Drivers.h"
//#include "States/PlayerState.h"

//enum DIRECTION { RIGHT, DOWN, LEFT, UP, NOT_MOVING };
class PlayerState;

class HumanPlayer : public Observer {
public:
	HumanPlayer(Map* m, int startX, int startY, int red, int green, int blue, int index);
	~HumanPlayer();
	bool update();
	void draw();
	void changeDirection(int newDirection);
	int getTileX();
	int getTileY();
	int getScore();
	int getPosX();
	int getPosY();
	void ghostCollision(int ghostState);
	bool isAlive();
	bool isBig();
	void die();
	friend class PlayerState;
	void changeState(PlayerState* s);
	virtual void observerUpdate(Subject*);

private:
	int tileSize;
	int tileWidth;
	int tileHeight;
	int height;
	int width;
	int score;
	int x;
	int y;
	int dir;
	int r;
	int g;
	int b;
	Map* map;
	bool moveLeft();
	bool moveRight();
	bool moveUp();
	bool moveDown();
	void snapTileX();
	void snapTileY();
	int getTileOffsetX();
	int getTileOffsetY();
	void eatPellet();
	EventQueue* eq;
	PlayerState* state;
	int index;
};

#endif