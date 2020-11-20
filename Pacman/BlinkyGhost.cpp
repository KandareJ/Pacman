#include "BlinkyChaseState.h"
#include "GhostHouseState.h"
#include "BlinkyScatterState.h"
#include "FrightenedState.h"
#include "HumanPlayer.h"
#include "allegro5/allegro_primitives.h"
#include <iostream>

BlinkyGhost::BlinkyGhost(Map* map, HumanPlayer* player) {
	state = new GhostHouseState(map, player, this);
	return;
}

BlinkyGhost::~BlinkyGhost() {
	return;
}

bool BlinkyGhost::update() {
	return state->update();
}

void BlinkyGhost::draw() {
	state->draw();
}

void BlinkyGhost::changeState(GhostState* newState) {
	delete state;
	state = newState;
}

void BlinkyGhost::frighten() {
	state->frighten();
}

void BlinkyGhost::chase() {
	state->chase();
}

void BlinkyGhost::scatter() {
	state->scatter();
}