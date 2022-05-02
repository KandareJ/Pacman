#include "./Joystick.h"

Joystick::Joystick(int joystickIndex) {
	joystickHandle = al_get_joystick(joystickIndex);
}

Joystick::~Joystick() {

}

void Joystick::update() {
	ALLEGRO_JOYSTICK_STATE joystickState;
	al_get_joystick_state(joystickHandle, &joystickState);

	JoystickPosition joystickPosition = axesToPosition(joystickState.stick[0].axis[0], joystickState.stick[0].axis[1]);

	if (joystickPosition != previousJoystickPosition) {
		previousJoystickPosition = joystickPosition;
		notify();
	}

	
	for (int i = 0; i < NUM_JOYSTICK_BUTTONS; i++) {
		ButtonPosition buttonPosition = buttonToPosition(joystickState.button[i]);
		if (buttonPosition != previousButtonPositions[i]) {
			previousButtonPositions[i] = buttonPosition;
			notify();
		}
	}
}

JoystickPosition Joystick::axesToPosition(double horizontalAxis, double verticalAxis) {
	const double THRESHOLD = 0.95;

	if (horizontalAxis > THRESHOLD) return JoystickPosition::RIGHT;
	else if (horizontalAxis < -THRESHOLD) return JoystickPosition::LEFT;
	else if (verticalAxis > THRESHOLD) return JoystickPosition::DOWN;
	else if (verticalAxis < -THRESHOLD) return JoystickPosition::UP;
	else return JoystickPosition::CENTER;
}

ButtonPosition Joystick::buttonToPosition(double buttonValue) {
	if (buttonValue) return ButtonPosition::DOWN;
	else return ButtonPosition::UP;
}