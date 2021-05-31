#ifndef DEAD_STATE_H
#define DEAD_STATE_H

#include "PlayerState.h"

class DeadState : public PlayerState {
public:
    DeadState(HumanPlayer* c);
    bool isAlive();
    void draw(int x, int y, int dir, int r, int g, int b);
};

#endif