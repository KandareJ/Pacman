#include "Input.h"

Input::Input() {
    int numJoysticks = al_get_num_joysticks();

    for (int i = 0; i < numJoysticks; i++) {
        inputDevices.push_back(new Joystick(i));
    }

    KeyMapping keyMapping;
    keyMapping.upKey = ALLEGRO_KEY_W;
    keyMapping.downKey = ALLEGRO_KEY_S;
    keyMapping.leftKey = ALLEGRO_KEY_A;
    keyMapping.rightKey = ALLEGRO_KEY_D;
    keyMapping.forwardButtonKey = ALLEGRO_KEY_ENTER;
    keyMapping.backwardButtonKey = ALLEGRO_KEY_ESCAPE;
    inputDevices.push_back(new KeyboardController(keyMapping));

    KeyMapping keyMapping2;
    keyMapping2.upKey = ALLEGRO_KEY_UP;
    keyMapping2.downKey = ALLEGRO_KEY_DOWN;
    keyMapping2.leftKey = ALLEGRO_KEY_LEFT;
    keyMapping2.rightKey = ALLEGRO_KEY_RIGHT;
    keyMapping2.forwardButtonKey = ALLEGRO_KEY_E;
    keyMapping2.backwardButtonKey = ALLEGRO_KEY_Q;
    inputDevices.push_back(new KeyboardController(keyMapping2));
}

Input::~Input() {
    
}

int Input::getInputDevicesSize() {
    return inputDevices.size();
}

void Input::attachAll(Observer* observer) {
    for (unsigned int i = 0; i < inputDevices.size(); i++) {
        inputDevices.at(i)->attach(observer);
    }
}

void Input::detach(Observer* observer, int index) {
    if (index < 0 || index >= inputDevices.size()) return;
    inputDevices.at(index)->detach(observer);
}

void Input::detachAll(Observer* observer) {
    for (unsigned int i = 0; i < inputDevices.size(); i++) {
        inputDevices.at(i)->detach(observer);
    }
}

void Input::attach(Observer* observer, int index) {
    if (index < 0 || index >= inputDevices.size()) return;
    inputDevices.at(index)->attach(observer);
}

void Input::update() {
    for (unsigned int i = 0; i < inputDevices.size(); i++) {
        inputDevices.at(i)->update();
    }
}