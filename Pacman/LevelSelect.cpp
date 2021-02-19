#include "LevelSelect.h"
#include "ClassicGame.h"
#include "MainMenu.h"
#include <iostream>
using namespace std;

LevelSelect::LevelSelect(GameEngine* c) {
	context = c;
	int numLevels;
	ifstream registry("levels/REGISTRY.pacr");
	string line;
	getline(registry, line);

	istringstream is(line);
	is >> numLevels;

	for (int i = 0; i < numLevels; i++) {
		getline(registry, line);
		levels.push_back(line);
	}

	registry.close();

	changed = true;
	selected = 0;
	return;
}

LevelSelect::~LevelSelect() {
	return;
}

bool LevelSelect::run(ALLEGRO_EVENT events) {
	if (events.type == ALLEGRO_EVENT_TIMER) {
		if (update()) draw();
	}

	else if (events.type == ALLEGRO_EVENT_KEY_DOWN) {
		switch (events.keyboard.keycode) {
		case ALLEGRO_KEY_ENTER:
			context->changeState(new ClassicGame(context, levels.at(selected)));
			break;
		case ALLEGRO_KEY_S:
			selected = ++selected % levels.size();
			changed = true;
			break;
		case ALLEGRO_KEY_W:
			selected = (--selected + levels.size()) % levels.size();
			changed = true;
			break;
		case ALLEGRO_KEY_ESCAPE:
			return true;
		}
	}

	else if (events.type == ALLEGRO_EVENT_JOYSTICK_BUTTON_DOWN) {
		switch (events.joystick.button) {
			case 0:
				context->changeState(new ClassicGame(context, levels.at(selected)));
				break;
			case 1:
				context->changeState(new MainMenu(context));
				break;
		}
	}

	else if (events.type == ALLEGRO_EVENT_JOYSTICK_AXIS) {
		/*
		if (events.joystick.axis == 0 && events.joystick.pos > 0.9) cout << "Right" << endl;
		else if (events.joystick.axis == 0 && events.joystick.pos < -0.9) cout << "Left" << endl;
		else if (events.joystick.axis == 1 && events.joystick.pos > 0.9) cout << "Down" << endl;
		else if (events.joystick.axis == 1 && events.joystick.pos < -0.9) cout << "Up" << endl;
		*/
		if (events.joystick.axis == 1 && events.joystick.pos < -0.95) {
			selected = (--selected + levels.size()) % levels.size();
			changed = true;
		}
		else if (events.joystick.axis == 1 && events.joystick.pos > 0.95) {
			selected = ++selected % levels.size();
			changed = true;
		}
	}



	return false;
}

bool LevelSelect::update() {
	if (changed) {
		changed = false;
		return true;
	}
	return false;
}

void LevelSelect::draw() {
	al_clear_to_color(al_map_rgb(0, 0, 0));
	Draw::instance()->drawLevelSelect(levels, selected);
	al_flip_display();
	return;
}
