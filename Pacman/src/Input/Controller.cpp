#include "Controller.h"

Controller::Controller() {
    previousJoystickPosition = JoystickPosition::CENTER;

	for (int i = 0; i < NUM_JOYSTICK_BUTTONS; i++) {
		previousButtonPositions[i] = ButtonPosition::UP;
	}
}

JoystickPosition Controller::getPreviousJoystickPosition() {
	return previousJoystickPosition;
}

ButtonPosition Controller::getPreviousButtonPosition(int index) {
	if (index >= NUM_JOYSTICK_BUTTONS || index < 0) return ButtonPosition::UP;
	else return previousButtonPositions[index];
}