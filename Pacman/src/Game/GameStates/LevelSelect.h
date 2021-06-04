#ifndef LEVELSELECT_H
#define LEVELSELECT_H

#include "Game.h"
#include "../../Graphics/Draw.h"
#include "../GameInfo.h"
#include <allegro5/allegro.h>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

class LevelSelect : public Game {
public:
	LevelSelect(GameEngine* c, GameInfo settings);
	~LevelSelect();
	bool run(ALLEGRO_EVENT events);

private:
	bool update();
	void draw();
	std::vector<std::string> levels;
	int selected;
	bool changed;
	GameEngine* context;
	GameInfo settings;
};

#endif // !LEVELSELECT_H
