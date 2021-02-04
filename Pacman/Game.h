#ifndef GAME_H
#define GAME_H

#include <allegro5/allegro.h>
#include "GameEngine.h"

class Game {
public:
	virtual bool run(ALLEGRO_EVENT events) = 0;
};

#endif