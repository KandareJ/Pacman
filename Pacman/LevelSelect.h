#ifndef LEVELSELECT_H
#define LEVELSELECT_H

#include "Game.h"
#include "Draw.h"
#include <allegro5/allegro.h>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

class LevelSelect : public Game {
public:
	LevelSelect(GameEngine* c);
	~LevelSelect();
	bool run(ALLEGRO_EVENT events);

private:
	bool update();
	void draw();
	std::vector<std::string> levels;
	int selected;
	bool changed;
	GameEngine* context;
};

#endif // !LEVELSELECT_H
