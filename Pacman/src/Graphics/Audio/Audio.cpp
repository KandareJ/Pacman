#include "Audio.h"
#include <iostream>

using namespace std;

Audio* Audio::_instance = 0;

Audio* Audio::instance() {
	if (_instance == 0) {
		_instance = new Audio();
	}
	return _instance;
}

Audio::Audio() {
    deathSound = al_load_sample("assets/sounds/pacman_death.wav");
    eatGhostSound = al_load_sample("assets/sounds/pacman_eatghost.wav");
    eatFruitSound = al_load_sample("assets/sounds/pacman_eatfruit.wav");
    powerUpSound = al_load_sample("assets/sounds/powerup.wav");
    menuMoveSound = al_load_sample("assets/sounds/menu_move.wav");
    menuSelectSound = al_load_sample("assets/sounds/menu_select.wav");
    al_reserve_samples(3);
}

Audio::~Audio() {
    al_destroy_sample(deathSound);
}

// game play
void Audio::death() {
    al_play_sample(deathSound, 1.0f, 0.0f, 1.0f, ALLEGRO_PLAYMODE_ONCE, NULL);
    return;
}

void Audio::eatGhost() {
    al_play_sample(eatGhostSound, 1.0f, 0.0f, 1.0f, ALLEGRO_PLAYMODE_ONCE, NULL);
    return;
}

void Audio::eatFruit() {
    al_play_sample(eatFruitSound, 1.0f, 0.0f, 1.0f, ALLEGRO_PLAYMODE_ONCE, NULL);
    return;
}

void Audio::powerUp() {
    al_play_sample(powerUpSound, 1.0f, 0.0f, 1.0f, ALLEGRO_PLAYMODE_ONCE, NULL);
    return;
}

void Audio::endPowerUp() {
    return;
}

// menu
void Audio::menuMove() {
    al_play_sample(menuMoveSound, 1.0f, 0.0f, 1.0f, ALLEGRO_PLAYMODE_ONCE, NULL);
    return;
}

void Audio::menuSelect() {
    al_play_sample(menuSelectSound, 1.0f, 0.0f, 1.0f, ALLEGRO_PLAYMODE_ONCE, NULL);
    return;
}