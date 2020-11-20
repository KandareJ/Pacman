#ifndef GHOSTHOUSESTATE_H
#define GHOSTHOUSESTATE_H

#include "GhostState.h"
#include "BlinkyGhost.h"
#include "Map.h"
#include "HumanPlayer.h"
#include "Draw.h"
#include <vector>

using namespace std;

class GhostHouseState : public GhostState {
public:
	GhostHouseState(Map* map, HumanPlayer* player, BlinkyGhost* c);
	~GhostHouseState();
	void draw();
	bool update();
	void frighten();
private:
	int choosePath(vector<int> options);
};

#endif