#include "PlayerState.h"
#include "BigPlayerState.h"
#include "DyingState.h"
#include "../../Graphics/Audio/Audio.h"

PlayerState::PlayerState(HumanPlayer* c) {
    frame = 0;
    context = c;
    return;
}

PlayerState::~PlayerState() {
    return;
}

bool PlayerState::update() {
    frame = ++frame % 8;
    return true;
}

void PlayerState::draw(int x, int y, int dir, int r, int g, int b) {
	Draw* draw = Draw::instance();
    draw->drawPlayer(x, y, dir, frame, r, g, b);
}

void PlayerState::ghostCollision(int ghostState) {
    if (ghostState == 0) die(); // change state to dead
    else if (ghostState == 1) Audio::instance()->eatGhost();
    return;
}

bool PlayerState::isAlive() {
    return true;
}

bool PlayerState::isBig() {
    return false;
}

void PlayerState::die() {
    Audio::instance()->death();
    context->changeState(new DyingState(context));
    return;
}

void PlayerState::powerUp() {
    // change state to power up
    Audio::instance()->powerUp();
    context->changeState(new BigPlayerState(context));
    return;
}

bool PlayerState::canMove() {
    return true;
}