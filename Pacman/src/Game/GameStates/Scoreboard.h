#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include "Game.h"
#include "../GameEngine.h"
#include "../GameInfo.h"
#include <vector>
#include <allegro5/allegro.h>

class Scoreboard : public Game {
public:
	Scoreboard(GameEngine* c, GameInfo g);
	~Scoreboard();
	bool run(ALLEGRO_EVENT events);

private:
	bool update();
	void draw();
	bool changed;
	GameEngine* context;
	GameInfo gameInfo;
	int selected;
};

#endif // !SCOREBOARD_H
