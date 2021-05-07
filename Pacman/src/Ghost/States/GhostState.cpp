#include "GhostState.h"

GhostState::~GhostState() {
	return;
}

void GhostState::changeState(GhostState* s) {
	context->changeState(s);
}

bool GhostState::update(double pelletPercent) {

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

int GhostState::getPosX() {
	return getTileX() * tileSize + getTileOffsetX();
}

int GhostState::getPosY() {
	return getTileY() * tileSize + getTileOffsetY();
}

int GhostState::getTileX() {
	return x / tileSize % tileWidth;
}

int GhostState::getTileY() {
	return y / tileSize % tileHeight;
}

void GhostState::snapTileX() {
	x = (int)(x / tileSize) * tileSize + (tileSize / 2);
}

void GhostState::snapTileY() {
	y = (int)(y / tileSize) * tileSize + (tileSize / 2);
}

int GhostState::getTileOffsetX() {
	return (x - getTileX() * tileSize - (tileSize / 2));
}
int GhostState::getTileOffsetY() {
	return (y - getTileY() * tileSize - (tileSize / 2));
}

bool GhostState::moveLeft() {
	if (isValidTile(getTileX() - 1, getTileY()) || getTileOffsetX() > 0) {
		if (x <= 0)x = width;
		x -= speed;
	}
	if (getTileX() != lastTileX && getTileOffsetX() <= 0) {
		changeDirection();
	}
	return true;
}

bool GhostState::moveRight() {
	if (isValidTile(getTileX() + 1, getTileY()) || getTileOffsetX() < 0) {
		if (x >= width) x = 0;
		x += speed;
	}
	if (getTileX() != lastTileX && getTileOffsetX() >= 0) {
		changeDirection();
	}
	return true;
}

bool GhostState::moveUp() {
	if (isValidTile(getTileX(), getTileY() - 1) || getTileOffsetY() > 0) {
		if (y <= 0) y = height;
		y -= speed;
	}
	if (getTileY() != lastTileY && getTileOffsetY() <= 0) {
		changeDirection();
	}
	return true;
}

bool GhostState::moveDown() {
	if (isValidTile(getTileX(), getTileY() + 1) || getTileOffsetY() < 0) {
		if (y >= height) y = 0;
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
	return (map->getMapPos((tileWidth + tileX % tileWidth) % tileWidth, (tileHeight + tileY % tileHeight) % tileHeight) == 0);
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

void GhostState::frighten() {

}

void GhostState::scatter(int targetX, int targetY) {

}

void GhostState::chase(HumanPlayer* target) {

}

//returns 0 normally. Frightened State returns 1.
int GhostState::collision() {
	return 0;
}