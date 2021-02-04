#ifndef SCOREBOARD_H
#define SCORE_BOARD_H

#include "Game.h"
#include "GameEngine.h"
#include <vector>
#include <allegro5/allegro.h>

class Scoreboard : public Game {
public:
	Scoreboard(GameEngine* c, std::vector<int> s);
	~Scoreboard();
	bool run(ALLEGRO_EVENT events);

private:
	bool update();
	void draw();
	bool changed;
	GameEngine* context;
	std::vector<int> scores;
	int selected;
};

#endif // !SCOREBOARD_H
