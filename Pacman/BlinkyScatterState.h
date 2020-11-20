#ifndef BLINKYSCATTERSTATE_H
#define BLINKYSCATTERSTATE_H

#include "GhostState.h"
#include "Map.h"
#include "HumanPlayer.h"
#include <vector>
#include "Draw.h"

using namespace std;

class BlinkyScatterState : public GhostState {
public:
	BlinkyScatterState(int x, int y, Map* map, HumanPlayer* player, BlinkyGhost* c);
	~BlinkyScatterState();
	void draw();
	void frighten();
	void chase();

private:
	int choosePath(vector<int> options);
};

#endif