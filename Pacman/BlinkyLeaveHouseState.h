#ifndef GHOSTLEAVEHOUSESTATE_H
#define GHOSTLEAVEHOUSESTATE_H

#include "GhostState.h"
#include "BlinkyGhost.h"
#include "Map.h"
#include "HumanPlayer.h"
#include "Draw.h"
#include <vector>

using namespace std;

class BlinkyLeaveHouseState : public GhostState {
public:
	BlinkyLeaveHouseState(int x, int y, Map* map, HumanPlayer* player, BlinkyGhost* c);
	~BlinkyLeaveHouseState();
	void draw();
	bool update();
	void frighten();
private:
	int choosePath(vector<int> options);
	bool moveUp();
};

#endif