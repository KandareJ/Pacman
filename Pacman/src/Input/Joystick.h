#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <queue>
#include <allegro5/allegro.h>

#include "./Controller.h"

class Joystick : public Controller {
public:
	Joystick(int);
	~Joystick();
	void update();
private:
	JoystickPosition axesToPosition(double, double);
	ButtonPosition buttonToPosition(double);
	ALLEGRO_JOYSTICK* joystickHandle;
};

#endif