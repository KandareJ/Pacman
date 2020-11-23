#ifndef BASICGHOST_H
#define BASICGHOST_H

#include "Map.h"
#include "HumanPlayer.h"

class GhostState;

class BasicGhost {
public:
	BasicGhost(Map* map, HumanPlayer* player, double pelletPercent);
	~BasicGhost();
	bool update();
	void draw();
	void frighten();
	void scatter(int targetX, int targetY);
	void chase(HumanPlayer* target);
	int getPosX();
	int getPosY();
	int collision();

private:
	friend class GhostState;
	void changeState(GhostState* s);
	GhostState* state;
	int r;
	int g;
	int b;
	int minHouseTime;
	double pelletPercent;
};

#endif