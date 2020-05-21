#ifndef BLINKYCHASESTATE_H
#define BLINKYCHASESTATE_H

#include "GhostState.h"
#include "Map.h"
#include "HumanPlayer.h"
#include <vector>
#include "Draw.h"

using namespace std;

class BlinkyChaseState : public GhostState {
public:
	BlinkyChaseState(int x, int y, Map* map, HumanPlayer* player, BlinkyGhost* c);
	~BlinkyChaseState();
	void draw();
	bool update();

private:
	int choosePath(vector<int> options);
};

#endif