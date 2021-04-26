#ifndef MAINMENU_H
#define MAINMENU_H

#include "Game.h"
#include "../../Graphics/Draw.h"
#include "../GameEngine.h"
#include <allegro5/allegro.h>

class MainMenu : public Game {
public:
	MainMenu(GameEngine* c);
	~MainMenu();
	bool run(ALLEGRO_EVENT events);

private:
	GameEngine* context;
	int frame;
	bool update();
	void draw();
};

#endif // !MAINMENU_H
