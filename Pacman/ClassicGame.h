#ifndef CLASSICGAME_H
#define CLASSICGAME_H

#include <allegro5/allegro.h>
#include <vector>
#include "Game.h"
#include "GameEngine.h"
#include "HumanPlayer.h"
#include "BasicGhost.h"
#include "ClassicMap.h"
#include "Map.h"
#include "EventQueue.h"
#include <iostream>
#include <string>

using namespace std;

class ClassicGame : public Game {
public:
	ClassicGame(GameEngine* c, string level);
	~ClassicGame();
	bool run(ALLEGRO_EVENT events);
	HumanPlayer* getPlayer();
	Map* getMap();
	void frighten();
	void scatter();
	void chase();
private:
	GameEngine* context;
	bool over;
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
	int getChasePlayer();
	int lastChasePlayer;
	vector<ALLEGRO_JOYSTICK*> joysticks;
};

#endif