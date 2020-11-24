#ifndef CLASSICONEPLAYERGAME_H
#define CLASSICONEPLAYERGAME_H

#include <allegro5/allegro.h>
#include <vector>
#include "HumanPlayer.h"
#include "BasicGhost.h"
#include "ClassicMap.h"
#include "Map.h"
#include "EventQueue.h"
#include <iostream>

using namespace std;

class ClassicOnePlayerGame {
public:
	ClassicOnePlayerGame();
	~ClassicOnePlayerGame();
	bool run(ALLEGRO_EVENT events);
	HumanPlayer* getPlayer();
	Map* getMap();
	void frighten();
	void scatter();
	void chase();
private:
	Map* map;
	vector<HumanPlayer*> players;
	vector<BasicGhost*> ghosts;
	bool update();
	void draw();
	EventQueue* eq;
	void raiseEvents();
	int scatterChase;
	void detectCollisions();
	double getDistance(int tileX1, int tileY1, int tileX2, int tileY2);
};

#endif