#ifndef BASICGHOST_H
#define BASICGHOST_H

#include "../Map/Map.h"
#include "../Player/HumanPlayer.h"

class GhostState;

class BasicGhost {
public:
	BasicGhost(Map* map, HumanPlayer* player, double pelletPercent, int r, int g, int b);
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
	void generateGhostColor();
	void hsv_to_rgb(int h, int s, int v);
	void changeState(GhostState* s);
	GhostState* state;
	int r;
	int g;
	int b;
	int minHouseTime;
	double pelletPercent;
};

#endif