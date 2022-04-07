#ifndef DRIVERS_H
#define DRIVERS_H

#include "../Input/Input.h"

class Drivers {
public:
    static Drivers* getDrivers();
    Input* getInput();
protected:
    Drivers();
private:
    static Drivers* drivers;
    Input* input;

};

#endif