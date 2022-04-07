#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <queue>
#include <allegro5/allegro.h>

#include "../Utils/Subject.h"
#include "JoystickConstants.h"

class Joystick : public Subject {
public:
	Joystick(int);
	~Joystick();
	void update();
	JoystickPosition getPreviousJoystickPosition();
	ButtonPosition getPreviousButtonPosition(int);
private:
	JoystickPosition axesToPosition(double, double);
	ButtonPosition buttonToPosition(double);
	ALLEGRO_JOYSTICK* joystickHandle;
	JoystickPosition previousJoystickPosition;
	ButtonPosition previousButtonPositions[NUM_JOYSTICK_BUTTONS];
};

#endif