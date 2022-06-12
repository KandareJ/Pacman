#include "Subject.h"

Subject::Subject() {

}

Subject::~Subject() {

}

void Subject::attach(Observer* o) {
	observers.push_back(o);
}

void Subject::detach(Observer* o) {
	unsigned int size = observers.size();

	for (unsigned int i = 0; i < size; i++) {
		if (observers.at(i) == o) {
			observers.erase(observers.begin() + i);
			break;
		}
	}
}

void Subject::notify() {
	unsigned int size = observers.size();

	for (unsigned int i = 0; i < size; i++) {
		observers.at(i)->observerUpdate(this);
	}
}
