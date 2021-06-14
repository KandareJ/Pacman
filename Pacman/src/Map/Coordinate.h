#ifndef COORDINATE_H
#define COORDINATE_H

class Coordinate {
public:
	Coordinate(int x, int y) {
		this->x = x;
		this->y = y;
	}
	Coordinate() {
		x = 0;
		y = 0;
	}
	int x;
	int y;
};

#endif // !COORDINATE_H
