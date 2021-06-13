#include "Scoreboard.h"
#include "../../Graphics/Draw.h"
#include "MainMenu.h"
#include "GameSettings.h"
#include "../../Graphics/Audio/Audio.h"

Scoreboard::Scoreboard(GameEngine* c, GameInfo g) {
	context = c;
	changed = true;
	selected = 0;
	gameInfo = g;
	return;
}

Scoreboard::~Scoreboard() {
	return;
}

bool Scoreboard::run(ALLEGRO_EVENT events) {
	if (events.type == ALLEGRO_EVENT_TIMER) {
		if (update()) draw();
	}

	else if (events.type == ALLEGRO_EVENT_KEY_DOWN) {
		switch (events.keyboard.keycode) {
		case ALLEGRO_KEY_RSHIFT:
			Audio::instance()->menuSelect();
			context->changeState(new MainMenu(context));
			break;
		case ALLEGRO_KEY_ENTER:
			Audio::instance()->menuSelect();
			context->changeState(new GameSettings(context, gameInfo));
			break;
		case ALLEGRO_KEY_S:
			Audio::instance()->menuMove();
			selected = ++selected % gameInfo.players.size();
			changed = true;
			break;
		case ALLEGRO_KEY_W:
			Audio::instance()->menuMove();
			selected = (--selected + gameInfo.players.size()) % gameInfo.players.size();
			changed = true;
			break;
		case ALLEGRO_KEY_ESCAPE:
			return true;
		}
	}


	else if (events.type == ALLEGRO_EVENT_JOYSTICK_BUTTON_DOWN) {
		switch (events.joystick.button) {
			case 0:
				Audio::instance()->menuSelect();
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
			Audio::instance()->menuMove();
			selected = (--selected + gameInfo.players.size()) % gameInfo.players.size();
			changed = true;
		}
		else if (events.joystick.axis == 1 && events.joystick.pos > 0.95) {
			Audio::instance()->menuMove();
			selected = ++selected % gameInfo.players.size();
			changed = true;
		}
	}

	return false;
}

void Scoreboard::draw() {
	al_clear_to_color(al_map_rgb(0, 0, 0));
	Draw::instance()->drawScoreboard(gameInfo.players, selected);
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