#include "Scoreboard.h"
#include "Draw.h"
#include "MainMenu.h"

Scoreboard::Scoreboard(GameEngine* c, std::vector<int> s) {
	context = c;
	changed = true;
	selected = 0;
	scores = s;
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
		case ALLEGRO_KEY_ENTER:
			context->changeState(new MainMenu(context));
			break;
		case ALLEGRO_KEY_S:
			selected = ++selected % scores.size();
			changed = true;
			break;
		case ALLEGRO_KEY_W:
			selected = (--selected + scores.size()) % scores.size();
			changed = true;
			break;
		case ALLEGRO_KEY_ESCAPE:
			return true;
		}
	}

	return false;
}

void Scoreboard::draw() {
	al_clear_to_color(al_map_rgb(0, 0, 0));
	Draw::instance()->drawScoreboard(scores, selected);
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