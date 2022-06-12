#include "KeyboardController.h"

KeyboardController::KeyboardController(KeyMapping keyMapping) {
    this->keyMapping = keyMapping;
}

void KeyboardController::update() {
    ALLEGRO_KEYBOARD_STATE keyboardState;
    al_get_keyboard_state(&keyboardState);

    if (al_key_down(&keyboardState, keyMapping.forwardButtonKey) && previousButtonPositions[0] != ButtonPosition::DOWN) {
        previousButtonPositions[0] = ButtonPosition::DOWN;
        notify();
    }

    else if (!al_key_down(&keyboardState, keyMapping.forwardButtonKey) && previousButtonPositions[0] == ButtonPosition::DOWN) {
        previousButtonPositions[0] = ButtonPosition::UP;
    } 

    else if (al_key_down(&keyboardState, keyMapping.backwardButtonKey) && previousButtonPositions[1] != ButtonPosition::DOWN) {
        previousButtonPositions[1] = ButtonPosition::DOWN;
        notify();
    }

    else if (!al_key_down(&keyboardState, keyMapping.backwardButtonKey) && previousButtonPositions[1] == ButtonPosition::DOWN) {
        previousButtonPositions[1] = ButtonPosition::UP;
    }

    else if (al_key_down(&keyboardState, keyMapping.upKey) && previousJoystickPosition != JoystickPosition::UP) {
        previousJoystickPosition = JoystickPosition::UP;
        notify();
    }

    else if (!al_key_down(&keyboardState, keyMapping.upKey) && previousJoystickPosition == JoystickPosition::UP) {
        previousJoystickPosition = JoystickPosition::CENTER;
        notify();
    }

    else if (al_key_down(&keyboardState, keyMapping.downKey) && previousJoystickPosition != JoystickPosition::DOWN) {
        previousJoystickPosition = JoystickPosition::DOWN;
        notify();
    }

    else if (!al_key_down(&keyboardState, keyMapping.downKey) && previousJoystickPosition == JoystickPosition::DOWN) {
        previousJoystickPosition = JoystickPosition::CENTER;
        notify();
    }

    else if (al_key_down(&keyboardState, keyMapping.leftKey) && previousJoystickPosition != JoystickPosition::LEFT) {
        previousJoystickPosition = JoystickPosition::LEFT;
        notify();
    }

    else if (!al_key_down(&keyboardState, keyMapping.leftKey) && previousJoystickPosition == JoystickPosition::LEFT) {
        previousJoystickPosition = JoystickPosition::CENTER;
        notify();
    }

    else if (al_key_down(&keyboardState, keyMapping.rightKey) && previousJoystickPosition != JoystickPosition::RIGHT) {
        previousJoystickPosition = JoystickPosition::RIGHT;
        notify();
    }

    else if (!al_key_down(&keyboardState, keyMapping.rightKey) && previousJoystickPosition == JoystickPosition::RIGHT) {
        previousJoystickPosition = JoystickPosition::CENTER;
        notify();
    }
}