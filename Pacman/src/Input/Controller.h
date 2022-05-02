#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "JoystickConstants.h"
#include "../Utils/Subject.h"

class Controller : public Subject {
public:
    Controller();
    virtual void update() = 0;
	JoystickPosition getPreviousJoystickPosition();
	ButtonPosition getPreviousButtonPosition(int);
protected:
    JoystickPosition previousJoystickPosition;
	ButtonPosition previousButtonPositions[NUM_JOYSTICK_BUTTONS];
};

#endif