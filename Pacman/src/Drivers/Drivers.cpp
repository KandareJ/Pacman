#include "Drivers.h"

Drivers* Drivers::drivers = 0;

Drivers* Drivers::getDrivers() {
    if (drivers == 0) {
        drivers = new Drivers();
    }
    return drivers;
}

Drivers::Drivers() {
    input = new Input();
}

Input* Drivers::getInput() {
    return input;
}