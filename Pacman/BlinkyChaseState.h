#ifndef BLINKYCHASESTATE_H
#define BLINKYCHASESTATE_H

#include "GhostState.h"
#include "Map.h"
#include "HumanPlayer.h"
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <time.h> 

using namespace std;

class BlinkyChaseState : public GhostState {
public:
	BlinkyChaseState(int x, int y, Map* map, HumanPlayer* player);
	~BlinkyChaseState();
	void draw();

private:
	int choosePath(vector<int> options);
};

#endif