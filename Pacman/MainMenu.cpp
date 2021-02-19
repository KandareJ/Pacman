#include "MainMenu.h"
#include "LevelSelect.h"
#include <iostream>

MainMenu::MainMenu(GameEngine* c) {
	context = c;
	frame = -1;
}

MainMenu::~MainMenu() {
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

	else if (events.type == ALLEGRO_EVENT_KEY_DOWN) {
		switch (events.keyboard.keycode) {
		case ALLEGRO_KEY_ENTER:
			context->changeState(new LevelSelect(context));
			return false;
		case ALLEGRO_KEY_ESCAPE:
			return true;
		}
	}

	else if (events.type == ALLEGRO_EVENT_JOYSTICK_BUTTON_DOWN) {
		switch (events.joystick.button) {
			case 0:
				context->changeState(new LevelSelect(context));
				return false;
			case 1:
				return true;
		}
	}

	return false;
}
