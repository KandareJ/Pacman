#include "BigPlayerState.h"
#include "ShrinkingPlayerState.h"

BigPlayerState::BigPlayerState(HumanPlayer* c) :  PlayerState(c) {
    counter = 0;
    return;
}

bool BigPlayerState::update() {
    frame = ++frame % 8;
    if (++counter >= 300) context->changeState(new ShrinkingPlayerState(context));
    return true;
}

void BigPlayerState::draw(int x, int y, int dir, int r, int g, int b) {
	Draw* draw = Draw::instance();
    draw->drawBigPlayer(x, y, dir, frame, r, g, b);
}

bool BigPlayerState::isBig() {
    return true;
}

void BigPlayerState::powerUp() {
    counter = 0;
    return;
}

void BigPlayerState::die() {
    return;
}

