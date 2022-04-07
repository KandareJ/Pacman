#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <allegro5/allegro.h>
#include "../Drivers/Drivers.h"

class Game;

class GameEngine {
public:
	GameEngine();
	~GameEngine();
	bool run(ALLEGRO_EVENT events);
	void changeState(Game* s);

private:
	friend class Game;
	Game* state;
};

#endif