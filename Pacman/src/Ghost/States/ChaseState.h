#ifndef CHASESTATE_H
#define CHASESTATE_H

#include "GhostState.h"
#include "../../Map/Map.h"
#include "../../Player/HumanPlayer.h"
#include "FrightenedState.h"
#include <vector>
#include "../../Graphics/Draw.h"

using namespace std;

class ChaseState : public GhostState {
public:
	ChaseState(int x, int y, Map* map, HumanPlayer* player, BasicGhost* c);
	~ChaseState();
	void draw(int r, int g, int b);
	void frighten();
	void scatter(int targetX, int targetY);

private:
	int choosePath(vector<int> options);
};

#endif