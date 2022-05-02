#ifndef KEYBOARD_CONTROLLER_H
#define KEYBOARD_CONTROLLER_H

#include <allegro5/allegro.h>
#include "Controller.h"
#include "KeyMapping.h"

class KeyboardController : public Controller {
public:
    KeyboardController(KeyMapping);
    void update();
private:
    KeyMapping keyMapping;
};

#endif