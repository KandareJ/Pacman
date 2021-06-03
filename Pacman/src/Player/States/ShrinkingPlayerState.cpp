#include "ShrinkingPlayerState.h"
#include "../../Graphics/Audio/Audio.h"

ShrinkingPlayerState::ShrinkingPlayerState(HumanPlayer* c) : PlayerState(c) {
    Audio::instance()->powerDown();
    counter = 0;
    shrinking = true;
    return;
}

bool ShrinkingPlayerState::update() {
    frame = ++frame % 8;
    ++counter;
    if (counter >= 30) context->changeState(new PlayerState(context)); // change state
    else if (counter % 10 == 0) shrinking = !shrinking;
    return true;
}

void ShrinkingPlayerState::draw(int x, int y, int dir, int r, int g, int b) {
	Draw* draw = Draw::instance();
    if (shrinking) draw->drawShrinkingPlayer(x, y, dir, frame, r, g, b, 10 - (counter % 10));
    else draw->drawShrinkingPlayer(x, y, dir, frame, r, g, b, counter % 10);
}

bool ShrinkingPlayerState::isBig() {
    return true;
}


void ShrinkingPlayerState::die() {
    return;
}