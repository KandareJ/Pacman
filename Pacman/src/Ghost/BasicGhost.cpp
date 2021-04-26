#include "States/ChaseState.h"
#include "States/GhostHouseState.h"
#include "States/ScatterState.h"
#include "States/FrightenedState.h"
#include "BasicGhost.h"
#include "allegro5/allegro_primitives.h"
#include <iostream>

BasicGhost::BasicGhost(Map* map, HumanPlayer* player, double pelletPercent, int r, int g, int b) {
	state = new GhostHouseState(map, player, this);
	this->r = r;
	this->g = g;
	this->b = b;
	this->pelletPercent = pelletPercent;
	return;
}

BasicGhost::~BasicGhost() {
	delete state;
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


