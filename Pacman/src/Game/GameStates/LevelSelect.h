#ifndef LEVELSELECT_H
#define LEVELSELECT_H

#include "Game.h"
#include "../../Graphics/Draw.h"
#include "../GameInfo.h"
#include "../../Drivers/Drivers.h"
#include <allegro5/allegro.h>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

class LevelSelect : public Game, public Observer {
public:
	LevelSelect(GameEngine* c, GameInfo* settings);
	~LevelSelect();
	bool run(ALLEGRO_EVENT events);
	virtual void observerUpdate(Subject*);
private:
	bool update();
	void draw();
	std::vector<std::string> levels;
	int selected;
	bool changed;
	GameEngine* context;
	GameInfo* settings;
};

#endif // !LEVELSELECT_H
