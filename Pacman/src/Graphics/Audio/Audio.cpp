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
    al_reserve_samples(5);

    deathSound = al_load_sample("assets/sounds/pacman_death.wav");
    eatGhostSound = al_load_sample("assets/sounds/pacman_eatghost.wav");
    eatFruitSound = al_load_sample("assets/sounds/pacman_eatfruit.wav");
    powerUpSound = al_load_sample("assets/sounds/powerup.wav");
    powerDownSound = al_load_sample("assets/sounds/powerdown.wav");
    chompSound = al_load_sample("assets/sounds/chomp.wav");
    

    menuMoveSound = al_load_sample("assets/sounds/menu_move.wav");
    menuSelectSound = al_load_sample("assets/sounds/menu_select.wav");
/*
    backgroundMusic = al_load_sample("assets/sounds/background.ogg");
    backgroundMusicInstance = al_create_sample_instance(backgroundMusic);

    al_set_sample_instance_playmode(backgroundMusicInstance, ALLEGRO_PLAYMODE_LOOP);
    al_set_sample_instance_gain(backgroundMusicInstance, 0.5f);
    al_attach_sample_instance_to_mixer(backgroundMusicInstance, al_get_default_mixer());
    al_play_sample_instance(backgroundMusicInstance);
*/
}

Audio::~Audio() {
    al_destroy_sample(deathSound);
    al_destroy_sample(eatGhostSound);
    al_destroy_sample(eatFruitSound);
    al_destroy_sample(powerUpSound);
    al_destroy_sample(powerDownSound);
    al_destroy_sample(chompSound);

    al_destroy_sample(menuMoveSound);
    al_destroy_sample(menuSelectSound);

    al_destroy_sample(backgroundMusic);
    al_destroy_sample_instance(backgroundMusicInstance);
}

// gameplay
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

void Audio::powerDown() {
    al_play_sample(powerDownSound, 1.0f, 0.0f, 1.0f, ALLEGRO_PLAYMODE_ONCE, NULL);
    return;
}

void Audio::chomp() {
    al_play_sample(chompSound, 0.25f, 0.0f, 1.0f, ALLEGRO_PLAYMODE_ONCE, NULL);
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