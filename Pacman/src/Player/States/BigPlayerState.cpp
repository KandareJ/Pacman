#include "BigPlayerState.h"
#include "ShrinkingPlayerState.h"
#include "DyingState.h"
#include "../../Graphics/Audio/Audio.h"

BigPlayerState::BigPlayerState(HumanPlayer* c) :  PlayerState(c) {
    counter = 0;
    speed = Draw::instance()->getTileSize() / 6;
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
    Audio::instance()->powerUp();
    return;
}

void BigPlayerState::die() {
    Audio::instance()->death();
    context->changeState(new DyingState(context));
    return;
}

