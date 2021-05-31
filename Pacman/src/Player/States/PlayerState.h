#ifndef PLAYER_STATE
#define PLAYER_STATE

#include "../HumanPlayer.h"
#include "../../Graphics/Draw.h"

class PlayerState {
public:
    PlayerState(HumanPlayer* c);
    virtual ~PlayerState();
	virtual bool update();
	virtual void draw(int x, int y, int dir, int r, int g, int b);
	virtual void ghostCollision(int ghostState);
	virtual bool isAlive();
	virtual bool isBig();
	virtual void die();
    virtual void powerUp();
	virtual bool canMove();
protected:
    int frame;
	HumanPlayer* context;
};

#endif