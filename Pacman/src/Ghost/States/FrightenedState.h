#ifndef FRIGHTENEDSTATE_H
#define FRIGHTENEDSTATE_H

#include "GhostState.h"
#include "../../Map/Map.h"
#include "../../Player/HumanPlayer.h"
#include "../../Graphics/Draw.h"
#include <vector>

using namespace std;

class FrightenedState : public GhostState {
public:
	FrightenedState(int x, int y, Map* map, HumanPlayer* player, BasicGhost* c);
	~FrightenedState();
	void draw(int r, int g, int b);
	bool update(double pelletPercent);
	void frighten();
	int collision();
private:
	int choosePath(vector<int> options);
	int frame;
};

#endif