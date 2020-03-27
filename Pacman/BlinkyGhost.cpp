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
	//delete state;
	cout << "states address: " << this->state << endl;
	state = newState;
	cout << "states new address: " << this->state << endl;
	system("pause");
}