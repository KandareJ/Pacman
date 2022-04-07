#ifndef INPUT_H
#define INPUT_H

#include <vector>
#include <allegro5/allegro.h>

#include "./Joystick.h"

class Input {
public:
    Input();
    ~Input();
    void update();
    int getInputDevicesSize();
    void attachAll(Observer*);
    void attach(Observer*, int index);
    void detachAll(Observer*);
    void detach(Observer*, int index);
private:
    std::vector<Joystick*> inputDevices;
};

#endif