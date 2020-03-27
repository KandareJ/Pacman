#ifndef CLASSICONEPLAYERGAME_H
#define CLASSICONEPLAYERGAME_H

#include <allegro5/allegro.h>
#include <vector>
#include "HumanPlayer.h"
#include "BlinkyGhost.h"
#include "ClassicMap.h"
#include "Map.h"
#include <iostream>

using namespace std;

class ClassicOnePlayerGame {
public:
	ClassicOnePlayerGame();
	~ClassicOnePlayerGame();
	bool run(ALLEGRO_EVENT events);
	HumanPlayer* getPlayer();
	Map* getMap();
private:
	Map* map;
	HumanPlayer *player;
	vector<BlinkyGhost> ghosts;
	bool update();
	void draw();
};

#endif