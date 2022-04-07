#include "Input.h"

Input::Input() {
    int numJoysticks = al_get_num_joysticks();
    //inputDevices = std::vector<Joystick>(numJoysticks);

    for (int i = 0; i < numJoysticks; i++) {
        inputDevices.push_back(new Joystick(i));
    }
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