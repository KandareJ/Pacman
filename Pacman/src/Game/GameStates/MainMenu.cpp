#include "MainMenu.h"
#include "GameSettings.h"
#include "../../Graphics/Audio/Audio.h"

MainMenu::MainMenu(GameEngine* c) {
	context = c;
	frame = -1;

	Drivers::getDrivers()->getInput()->attachAll(this);
	
	exit = false;
}

MainMenu::~MainMenu() {
	Drivers::getDrivers()->getInput()->detachAll(this);
	return;
}

bool MainMenu::update() {
	frame = ++frame % 90;
	return true;
}

void MainMenu::draw() {
	al_clear_to_color(al_map_rgb(0, 0, 0));
	Draw::instance()->drawMenu(frame);
	al_flip_display();
	return;
}

bool MainMenu::run(ALLEGRO_EVENT events) {
	if (events.type == ALLEGRO_EVENT_TIMER) {
		if (update()) draw();
	}

	return exit;
}

void MainMenu::observerUpdate(Subject* sub) {
	Joystick* joystick = (Joystick*) sub;

	if (joystick->getPreviousButtonPosition(0) == ButtonPosition::DOWN) {
		Audio::instance()->menuSelect();
		context->changeState(new GameSettings(context));
	}

	else if (joystick->getPreviousButtonPosition(1) == ButtonPosition::DOWN) {
		exit = true;
	}
}
