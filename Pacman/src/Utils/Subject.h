#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>
#include "Observer.h"

class Subject {
public:
	virtual ~Subject();
	virtual void attach(Observer*);
	virtual void detach(Observer*);
	virtual void notify();
protected:
	Subject();
private:
	std::vector<Observer*> observers;
};

#endif