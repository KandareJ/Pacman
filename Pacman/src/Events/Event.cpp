#include "Event.h"

Event::Event(int type) {
	this->type = type;
}

int Event::getType() {
	return type;
}