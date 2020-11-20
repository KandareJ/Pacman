#ifndef RANDOMGHOST_H
#define RANDOMGHOST_H

#include "Map.h"
//#include "GhostState.h"
#include "HumanPlayer.h"

class GhostState;

class BlinkyGhost {
public:
	BlinkyGhost(Map* map, HumanPlayer* player);
	~BlinkyGhost();
	bool update();
	void draw();
	void frighten();
	void scatter();
	void chase();

private:
	friend class GhostState;
	void changeState(GhostState* s);
	GhostState* state;
};

#endif