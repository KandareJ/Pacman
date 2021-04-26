#ifndef EVENT_QUEUE_H
#define EVENT_QUEUE_H

#include "Event.h"
#include <queue>

class EventQueue {
private:
	static EventQueue* instance;
	EventQueue();
	std::queue<Event*> eq;

public:
	static EventQueue* getInstance();
	void push(Event* e);
	Event* pop();
	bool empty();
	
};

#endif