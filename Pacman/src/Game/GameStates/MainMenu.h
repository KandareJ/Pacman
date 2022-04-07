#ifndef MAINMENU_H
#define MAINMENU_H

#include <allegro5/allegro.h>

#include "Game.h"
#include "../../Graphics/Draw.h"
#include "../GameEngine.h"
#include "../../Utils/Observer.h"
#include "../../Input/JoystickConstants.h"
#include "../../Drivers/Drivers.h"

class MainMenu : public Game, public Observer {
public:
	MainMenu(GameEngine* c);
	~MainMenu();
	bool run(ALLEGRO_EVENT events);
	virtual void observerUpdate(Subject*);

private:
	GameEngine* context;
	int frame;
	bool exit;
	bool update();
	void draw();
};

#endif // !MAINMENU_H
