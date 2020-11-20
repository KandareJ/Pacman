#include "EventQueue.h"


EventQueue::EventQueue() {
}

EventQueue* EventQueue::getInstance() {
	if (!instance) instance = new EventQueue();
	return instance;
}

void EventQueue::push(Event* e) {
	eq.push(e);
}

Event* EventQueue::pop() {
	Event* e = eq.front();
	eq.pop();
	return e;
}

bool EventQueue::empty() {
	return eq.empty();
}

EventQueue *EventQueue::instance = 0;