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
	FrightenedState(int x, int y, Map* map, HumanPlayer* player);
	~FrightenedState();
	void draw();
private:
	int choosePath(vector<int> options);
};

#endif