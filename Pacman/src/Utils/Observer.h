#ifndef OBSERVER_H
#define OBSERVER_H

class Subject;

class Observer {
public:
	virtual ~Observer();
	virtual void observerUpdate(Subject*) = 0;
protected:
	Observer();
};

#endif