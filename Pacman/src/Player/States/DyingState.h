#ifndef DYING_STATE_H
#define DYING_STATE_H

#include "PlayerState.h"
#include "DeadState.h"

class DyingState : public PlayerState {
public:
    DyingState(HumanPlayer* c);
    bool update();
    void draw(int x, int y, int dir, int r, int g, int b);
	bool isBig();
    void powerUp();
    void ghostCollision(int ghostState);
    void die();
    bool isAlive();
    bool canMove();
};

#endif