#include "GhostState.h"

void GhostState::draw() {
	return;
}

int GhostState::choosePath(vector<int> options) {
	return -1;
}

bool GhostState::update() {

	switch (dir) {
	case NOT_MOVING:
		changeDirection();
		return false;
	case UP:
		return moveUp();
	case DOWN:
		return moveDown();
	case LEFT:
		return moveLeft();
	case RIGHT:
		return moveRight();
	default:
		return false;
	};
}

int GhostState::getTileX() {
	return x / 40 % 20;
}

int GhostState::getTileY() {
	return y / 40 % 15;
}

void GhostState::snapTileX() {
	x = (int)(x / 40) * 40 + 20;
}

void GhostState::snapTileY() {
	y = (int)(y / 40) * 40 + 20;
}

int GhostState::getTileOffsetX() {
	return (x - getTileX() * 40 - 20);
}
int GhostState::getTileOffsetY() {
	return (y - getTileY() * 40 - 20);
}

bool GhostState::moveLeft() {
	if (isValidTile(getTileX() - 1, getTileY()) || getTileOffsetX() > 0) {
		if (x <= 0)x = 800;
		x -= speed;
	}
	if (getTileX() != lastTileX && getTileOffsetX() <= 0) {
		changeDirection();
	}
	return true;
}

bool GhostState::moveRight() {
	if (isValidTile(getTileX() + 1, getTileY()) || getTileOffsetX() < 0) {
		if (x >= 800) x = 0;
		x += speed;
	}
	if (getTileX() != lastTileX && getTileOffsetX() >= 0) {
		changeDirection();
	}
	return true;
}

bool GhostState::moveUp() {
	if (isValidTile(getTileX(), getTileY() - 1) || getTileOffsetY() > 0) {
		if (y <= 0) y = 600;
		y -= speed;
	}
	if (getTileY() != lastTileY && getTileOffsetY() <= 0) {
		changeDirection();
	}
	return true;
}

bool GhostState::moveDown() {
	if (isValidTile(getTileX(), getTileY() + 1) || getTileOffsetY() < 0) {
		if (y >= 600) y = 0;
		y += speed;
	}
	if (getTileY() != lastTileY && getTileOffsetY() >= 0) {
		changeDirection();
	}
	return true;
}

void GhostState::changeDirection() {
	vector<int> options = getOptions(getTileX(), getTileY());
	lastTileX = getTileX();
	lastTileY = getTileY();

	if (options.size() == 1)dir = options.at(0);
	else dir = choosePath(options);
}

bool GhostState::isValidTile(int tileX, int tileY) {
	return (map->getMapPos((20 + tileX % 20) % 20, (15 + tileY % 15) % 15) == 0);
}

vector<int> GhostState::getOptions(int tileX, int tileY) {
	vector<int> options = vector<int>();
	if (dir != LEFT && isValidTile(tileX + 1, tileY)) {
		options.push_back(RIGHT);
	}
	if (dir != RIGHT && isValidTile(tileX - 1, tileY)) {
		options.push_back(LEFT);
	}
	if (dir != DOWN && isValidTile(tileX, tileY - 1)) {
		options.push_back(UP);
	}
	if (dir != UP && isValidTile(tileX, tileY + 1)) {
		options.push_back(DOWN);
	}

	return options;
}

double GhostState::getDistance(int tileX1, int tileY1, int tileX2, int tileY2) {
	return sqrt((tileX1 - tileX2) * (tileX1 - tileX2) + (tileY1 - tileY2) * (tileY1 - tileY2));
}