#include "Scoreboard.h"
#include "../../Graphics/Draw.h"
#include "MainMenu.h"
#include "GameSettings.h"
#include "../../Graphics/Audio/Audio.h"

Scoreboard::Scoreboard(GameEngine* c, GameInfo* g) {
	context = c;
	changed = true;
	selected = 0;
	gameInfo = g;
	Drivers::getDrivers()->getInput()->attachAll(this);
	return;
}

Scoreboard::~Scoreboard() {
	Drivers::getDrivers()->getInput()->detachAll(this);
	return;
}

void Scoreboard::observerUpdate(Subject* subject) {
	 Joystick* joystick = (Joystick*) subject;

    if (joystick->getPreviousButtonPosition(0) == ButtonPosition::DOWN) {
        Audio::instance()->menuSelect();
		context->changeState(new GameSettings(context, gameInfo));
    }

    else if (joystick->getPreviousButtonPosition(1) == ButtonPosition::DOWN) {
        Audio::instance()->menuSelect();
		delete gameInfo;
		context->changeState(new MainMenu(context));
    }

    else {
        switch (joystick->getPreviousJoystickPosition()) {
        case JoystickPosition::UP:
            Audio::instance()->menuMove();
			selected = (--selected + gameInfo->players.size()) % gameInfo->players.size();
			changed = true;
            break;
        case JoystickPosition::DOWN:
            Audio::instance()->menuMove();
			selected = ++selected % gameInfo->players.size();
			changed = true;
            break;
        };
    }
}

bool Scoreboard::run(ALLEGRO_EVENT events) {
	if (events.type == ALLEGRO_EVENT_TIMER) {
		if (update()) draw();
	}

	return false;
}

void Scoreboard::draw() {
	al_clear_to_color(al_map_rgb(0, 0, 0));
	Draw::instance()->drawScoreboard(gameInfo->players, selected);
	al_flip_display();
	return;
}

bool Scoreboard::update() {
	if (changed) {
		changed = false;
		return true;
	}
	return false;
}