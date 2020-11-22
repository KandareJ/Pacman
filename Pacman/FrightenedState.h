#ifndef FRIGHTENEDSTATE_H
#define FRIGHTENEDSTATE_H

#include "GhostState.h"
#include "Map.h"
#include "HumanPlayer.h"
#include "Draw.h"
#include <vector>

using namespace std;

class FrightenedState : public GhostState {
public:
	FrightenedState(int x, int y, Map* map, HumanPlayer* player, BlinkyGhost* c);
	~FrightenedState();
	void draw();
	bool update();
	void frighten();
	int collision();
private:
	int choosePath(vector<int> options);
	int frame;
};

#endif