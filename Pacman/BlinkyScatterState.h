#ifndef BLINKYSCATTERSTATE_H
#define BLINKYSCATTERSTATE_H

#include "GhostState.h"
#include "Map.h"
#include "HumanPlayer.h"
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <time.h> 

using namespace std;

class BlinkyScatterState : public GhostState {
public:
	BlinkyScatterState(int x, int y, Map* map, HumanPlayer* player);
	~BlinkyScatterState();
	void draw();

private:
	int choosePath(vector<int> options);
};

#endif