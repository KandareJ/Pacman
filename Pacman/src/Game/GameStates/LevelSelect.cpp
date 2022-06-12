#include "LevelSelect.h"
#include "ClassicGame.h"
#include "CharacterSelectMenu.h"
#include "MainMenu.h"
#include "../../Graphics/Audio/Audio.h"

LevelSelect::LevelSelect(GameEngine* c, GameInfo* settings) {
	context = c;
	Drivers::getDrivers()->getInput()->attachAll(this);
	int numLevels;
	this->settings = settings;
	std::ifstream registry("levels/REGISTRY.pacr");
	std::string line;
	getline(registry, line);

	std::istringstream is(line);
	is >> numLevels;

	for (int i = 0; i < numLevels; i++) {
		getline(registry, line);
		levels.push_back(line);
	}

	levels.push_back("random");

	registry.close();

	changed = true;
	selected = 0;
	return;
}

LevelSelect::~LevelSelect() {
	Drivers::getDrivers()->getInput()->detachAll(this);
	return;
}

void LevelSelect::observerUpdate(Subject* subject) {
	Joystick* joystick = (Joystick*) subject;

    if (joystick->getPreviousButtonPosition(0) == ButtonPosition::DOWN) {
        Audio::instance()->menuSelect();
		if (selected != levels.size() - 1) settings->levels.push_back(levels.at(selected));
		else settings->levels.push_back(levels.at(rand() % (levels.size() - 1)));
		context->changeState(new ClassicGame(context, settings));
    }

    else if (joystick->getPreviousButtonPosition(1) == ButtonPosition::DOWN) {
        Audio::instance()->menuSelect();
		context->changeState(new CharacterSelectMenu(context, settings));
    }

    else {
        switch (joystick->getPreviousJoystickPosition()) {
        case JoystickPosition::UP:
            Audio::instance()->menuMove();
			selected = (--selected + levels.size()) % levels.size();
			changed = true;
            break;
        case JoystickPosition::DOWN:
            Audio::instance()->menuMove();
			selected = ++selected % levels.size();
			changed = true;
            break;
        };
    }
}

bool LevelSelect::run(ALLEGRO_EVENT events) {
	if (events.type == ALLEGRO_EVENT_TIMER) {
		if (update()) draw();
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
