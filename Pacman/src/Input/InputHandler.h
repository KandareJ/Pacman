#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <allegro5/allegro.h>

enum outputs {
    NONE,
    TIMER,
    PRIMARY,
    SECONDARY,
    UP,
    DOWN,
    LEFT,
    RIGHT,
};

class InputHandler {
public:
    static outputs handleInput(ALLEGRO_EVENT event) {
        return NONE;
    }
};


#endif