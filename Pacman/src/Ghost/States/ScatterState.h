#ifndef SCATTERSTATE_H
#define SCATTERSTATE_H

#include "GhostState.h"
#include "../../Map/Map.h"
#include "../../Player/HumanPlayer.h"
#include <vector>
#include "../../Graphics/Draw.h"

using namespace std;

class ScatterState : public GhostState {
public:
	ScatterState(int x, int y, Map* map, HumanPlayer* target, int targetX, int targetY, BasicGhost* c);
	~ScatterState();
	void draw(int r, int g, int b);
	void frighten();
	void chase(HumanPlayer* target);

private:
	int choosePath(vector<int> options);
	int targetX;
	int targetY;
};

#endif