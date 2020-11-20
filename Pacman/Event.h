#ifndef EVENT_H
#define EVENT

class Event {
public:
	Event(int type);
	int getType();

private:
	int type;

};

#endif