#include "DeadState.h"

DeadState::DeadState(HumanPlayer* c) : PlayerState(c) {
    return;
}

bool DeadState::isAlive() {
    return false;
}

void DeadState::draw(int x, int y, int dir, int r, int g, int b) {
    return;
}