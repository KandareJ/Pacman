#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <iostream>

#include "../Pacman/src/Graphics/Draw.h"
#include "BuilderMap.h"

const double FPS = 30.0;
int HEIGHT = 900;
int WIDTH = 1200;

int main(int argc, char** argv) {
    if (argc < 5) {
        std::cout << "Usage: Studio <height> <width> <depth> <filename>" << std::endl;
        return 1;
    }

    int w = atoi(argv[1]);
    int h = atoi(argv[2]);
    int d = atoi(argv[3]);

	if (w < 2 || w > 100 || h < 2 || h > 100 || d < 1 || d > 10) {
		std::cout << "Usage: Studio <width> <height> <depth> <filename>" << std::endl;
		std::cout << "width and height must be less than 100 and depth must be less than 10" << std::endl;
        return 1;
	}
    char* filename = argv[4];

	bool quit = false;
	al_init();
	al_install_joystick();
	al_init_primitives_addon();
	al_install_keyboard();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_image_addon();
	al_install_audio();
	al_init_acodec_addon();

	ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
	ALLEGRO_EVENT events;
	ALLEGRO_TIMER *timer = al_create_timer(1 / FPS);
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_timer_event_source(timer));

	ALLEGRO_MONITOR_INFO info;
	al_get_monitor_info(0, &info);
	WIDTH = info.x2 - info.x1;
	HEIGHT = info.y2 - info.y1;
	al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
	ALLEGRO_DISPLAY* display = al_create_display(WIDTH, HEIGHT);

	Draw* draw = Draw::instance();
	draw->initializeProportions(WIDTH, HEIGHT);
    BuilderMap map = BuilderMap(w, h, d, filename);
	al_start_timer(timer);

	while (!quit) {
		al_wait_for_event(queue, &events);
        quit = map.run(events);
	}

	al_destroy_timer(timer);
	al_destroy_display(display);

	return 0;
}
