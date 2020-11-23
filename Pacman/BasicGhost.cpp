#include "ChaseState.h"
#include "GhostHouseState.h"
#include "ScatterState.h"
#include "FrightenedState.h"
#include "BasicGhost.h"
#include "HumanPlayer.h"
#include "allegro5/allegro_primitives.h"
#include <iostream>

BasicGhost::BasicGhost(Map* map, HumanPlayer* player, double pelletPercent) {
	state = new GhostHouseState(map, player, this);
	r = rand() % 255;
	g = rand() % 255;
	b = rand() % 255;
	this->pelletPercent = pelletPercent;
	return;
}

BasicGhost::~BasicGhost() {
	return;
}

bool BasicGhost::update() {
	return state->update(pelletPercent);
}

void BasicGhost::draw() {
	state->draw(r, g, b);
}

void BasicGhost::changeState(GhostState* newState) {
	delete state;
	state = newState;
}

void BasicGhost::frighten() {
	state->frighten();
}

void BasicGhost::chase(HumanPlayer* target) {
	state->chase(target);
}

void BasicGhost::scatter(int targetX, int targetY) {
	state->scatter(targetX, targetY);
}

int BasicGhost::getPosX() {
	return state->getPosX();
}

int BasicGhost::getPosY() {
	return state->getPosY();
}

int BasicGhost::collision() {
	return state->collision();
}