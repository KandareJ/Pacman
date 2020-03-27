#include <iostream>
#include "ClassicOnePlayerGame.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

const double FPS = 30.0;

int main() {
	bool quit = false;
	al_init();
	al_install_joystick();
	al_init_primitives_addon();
	al_install_keyboard();

	ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
	ALLEGRO_EVENT events;
	ALLEGRO_TIMER *timer = al_create_timer(1 / FPS);
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_timer_event_source(timer));

	ALLEGRO_DISPLAY* display = al_create_display(800, 600);

	al_start_timer(timer);

	ClassicOnePlayerGame game = ClassicOnePlayerGame();

	while (!quit) {
		al_wait_for_event(queue, &events);
		quit = game.run(events);
	}

	al_destroy_display(display);

	return 0;
}