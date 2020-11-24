#ifndef RETURNHOUSESTATE_H
#define RETURNHOUSESTATE_H

#include "GhostState.h"
#include "GhostHouseState.h"

class ReturnHouseState : public GhostState {
public:
	ReturnHouseState(int x, int y, Map* map, HumanPlayer* player, BasicGhost* c);
	~ReturnHouseState();
	void draw(int r, int g, int b);
	bool update(double pelletPercent);
	int collision();
private:
	int choosePath(vector<int> options);
	bool isValidTile(int tileX, int tileY);
	int targetX;
	int targetY;
};

#endif