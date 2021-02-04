#include "GameEngine.h"
#include "MainMenu.h"

GameEngine::GameEngine() {
	state = new MainMenu(this);
	return;
}

GameEngine::~GameEngine() {
	delete state;
	return;
}

bool GameEngine::run(ALLEGRO_EVENT events) {
	return state->run(events);
}

void GameEngine::changeState(Game* s) {
	delete state;
	state = s;
}