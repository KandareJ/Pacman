#ifndef RANDOMGHOST_H
#define RANDOMGHOST_H

#include "Map.h"
#include "GhostState.h"
#include "HumanPlayer.h"

class BlinkyGhost {
public:
	BlinkyGhost(Map* map, HumanPlayer* player);
	~BlinkyGhost();
	bool update();
	void draw();
	void changeState(GhostState* state);

private:
	GhostState* state;
};

#endif