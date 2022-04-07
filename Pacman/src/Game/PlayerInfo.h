#ifndef PLAYER_INFO_H
#define PLAYER_INFO_H

#include <string>
#include "../Utils/Subject.h"
#include "../Input/JoystickConstants.h"
#include "../Input/Joystick.h"
#include "../Graphics/Audio/Audio.h"

const int NUM_OPTIONS = 2;

class PlayerInfo : public Observer {
public:
    PlayerInfo();
    ~PlayerInfo();
    virtual void observerUpdate(Subject*);
    int r;
    int g;
    int b;
    int selected;
    int score;
    int wins;
    int numNames;
    int numColors;
    std::string name;
    int nameSelection;
    int colorSelection;
    ALLEGRO_JOYSTICK* joystick;
    bool returned;
};

#endif