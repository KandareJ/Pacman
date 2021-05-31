#include "DyingState.h"
    
DyingState::DyingState(HumanPlayer* c) : PlayerState(c) {
    return;
}

bool DyingState::update() {
    frame = ++frame % 32;
    if (frame == 0) context->changeState(new DeadState(context));
    return true;
}

void DyingState::draw(int x, int y, int dir, int r, int g, int b) {
    Draw* draw = Draw::instance();
    draw->drawDyingPlayer(x, y, dir, frame, r, g, b);
    return;
}

bool DyingState::isBig() {
    return false;
}

void DyingState::powerUp() {
    return;
}

void DyingState::ghostCollision(int ghostState) {
    return;
}

void DyingState::die() {
    return;
}

bool DyingState::isAlive() {
    return true;
}

bool DyingState::canMove() {
    return false;
}