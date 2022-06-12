#ifndef FRIGHTENEDENDSTATE_H
#define FRIGHTENEDENDSTATE_H

#include "GhostState.h"
#include "../../Map/Map.h"
#include "../../Player/HumanPlayer.h"
#include "../../Graphics/Draw.h"
#include <vector>

class FrightenedEndState : public GhostState {
public:
	FrightenedEndState(int x, int y, Map* map, HumanPlayer* player, BasicGhost* c);
	~FrightenedEndState();
	void draw(int r, int g, int b);
	bool update(double pelletPercent);
	void frighten();
	int collision();
private:
	int choosePath(std::vector<int> options);
	int frame;
};

#endif