#include "PlayerInfo.h"

PlayerInfo::PlayerInfo() {
    r = 0;
    g = 0;
    b = 0;
    score = 0;
    wins = 0;
    selected = 0;
    nameSelection = 0;
    numColors = 18;
    numNames = 0;
}

PlayerInfo::~PlayerInfo() {

}

void PlayerInfo::observerUpdate(Subject* subject) {
    Joystick* _joystick = (Joystick*)subject;

    if (_joystick->getPreviousButtonPosition(0) == ButtonPosition::DOWN) {
    
    }

    else if (_joystick->getPreviousButtonPosition(1) == ButtonPosition::DOWN) {
        
    }

    else {
        switch (_joystick->getPreviousJoystickPosition()) {
        case JoystickPosition::UP:
            Audio::instance()->menuMove();
            selected = (selected + 1) % NUM_OPTIONS;
            break;
        case JoystickPosition::DOWN:
            Audio::instance()->menuMove();
            selected--;
            if (selected < 0) selected = NUM_OPTIONS - 1;
            break;
        case JoystickPosition::LEFT:
            Audio::instance()->menuMove();
            if (selected == 0) {
                nameSelection--;
                if (nameSelection < 0) nameSelection = numNames - 1;
            }
            else if (selected == 1) {
                colorSelection--;
                if (colorSelection < 0) colorSelection = 17;
            }
            break;
        case JoystickPosition::RIGHT:
            Audio::instance()->menuMove();
            if (selected == 0) {
                nameSelection = (nameSelection + 1) % numNames;
            }
            else if (selected == 1) {
                colorSelection = (colorSelection + 1) % 18;
            }
            break;
        };
    }
}