#ifndef GHOSTHOUSESTATE_H
#define GHOSTHOUSESTATE_H

#include "GhostState.h"
#include "BlinkyGhost.h"
#include "Map.h"
#include "HumanPlayer.h"
#include <allegro5/allegro_primitives.h>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <time.h> 

using namespace std;

class GhostHouseState : public GhostState {
public:
	GhostHouseState(Map* map, HumanPlayer* player, BlinkyGhost* const c);
	~GhostHouseState();
	void draw();
	bool update();
private:
	int choosePath(vector<int> options);
	BlinkyGhost* context;
};

#endif