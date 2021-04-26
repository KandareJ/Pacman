#ifndef GHOSTHOUSESTATE_H
#define GHOSTHOUSESTATE_H

#include "GhostState.h"
#include "../BasicGhost.h"
#include "../../Map/Map.h"
#include "../../Player/HumanPlayer.h"
#include "../../Graphics/Draw.h"
#include <vector>

using namespace std;

class GhostHouseState : public GhostState {
public:
	GhostHouseState(Map* map, HumanPlayer* player, BasicGhost* c);
	~GhostHouseState();
	void draw(int r, int g, int b);
	bool update(double pelletPercent);
	void frighten();
private:
	int choosePath(vector<int> options);
	int time;
};

#endif