#ifndef LEAVEHOUSESTATE_H
#define LEAVEHOUSESTATE_H

#include "GhostState.h"
#include "BasicGhost.h"
#include "Map.h"
#include "HumanPlayer.h"
#include "Draw.h"
#include <vector>

using namespace std;

class LeaveHouseState : public GhostState {
public:
	LeaveHouseState(int x, int y, Map* map, HumanPlayer* player, BasicGhost* c);
	~LeaveHouseState();
	void draw(int r, int g, int b);
	bool update(double pelletPercent);
private:
	int choosePath(vector<int> options);
	bool moveUp();
};

#endif