#include "HumanPlayer.h"
#include "allegro5/allegro_primitives.h"
#include <iostream>

using namespace std;

HumanPlayer::HumanPlayer(Map* m, int startX, int startY, int red, int green, int blue) {
	eq = eq->getInstance();
	Draw* draw = Draw::instance();
	tileSize = draw->getTileSize();
	tileWidth = draw->getTileWidth();
	tileHeight = draw->getTileHeight();
	height = tileHeight * tileSize;
	width = tileWidth * tileSize;

	map = m;
	x = startX * tileSize + (tileSize / 2);
	y = startY * tileSize + (tileSize / 2);
	dir = NOT_MOVING;
	score = 0;
	speed = tileSize / 8;
	frame = 0;
	state = 0;
	alive = true;
	r = red;
	g = green;
	b = blue;

	return;
}

HumanPlayer::~HumanPlayer() {
	return;
}

bool HumanPlayer::update() {
	if (!alive) return false;
	frame = ++frame % 8;
	if (state > 0) state--;
	switch (dir) {
	case NOT_MOVING:
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

int HumanPlayer::getTileX() {
	return x / tileSize % tileWidth;
}

int HumanPlayer::getTileY() {

	int tile = y / tileSize % tileHeight;
	return tile;
}

void HumanPlayer::snapTileX() {
	x = (int)(x / tileSize) * tileSize + (tileSize / 2);
}

void HumanPlayer::snapTileY() {
	y = (int)(y / tileSize) * tileSize + (tileSize / 2);
}

int HumanPlayer::getTileOffsetX() {
	return (x - getTileX() * tileSize - (tileSize / 2));
}
int HumanPlayer::getTileOffsetY() {
	return (y - getTileY() * tileSize - (tileSize / 2));
}

void HumanPlayer::draw() {
	if (!alive) return;
	Draw* draw = Draw::instance();
	if (state) draw->drawBigPlayer(x, y, dir, frame, r, g, b);
	else draw->drawPlayer(x, y, dir, frame, r, g, b);
	return;
}

bool HumanPlayer::moveLeft() {
	bool change = false;
	if (map->getMapPos((tileWidth + (getTileX() - 1) % tileWidth) % tileWidth, getTileY()) == 0 || getTileOffsetX() > 0) {
		if (x <= 0)x = width;
		x -= speed;
		change = true;
	}
	else dir = NOT_MOVING;
	eatPellet();
	return change;
}

bool HumanPlayer::moveRight() {
	bool change = false;
	if (map->getMapPos((tileWidth + (getTileX() + 1) % tileWidth) % tileWidth, getTileY()) == 0 || getTileOffsetX() < 0) {
		if (x >= width) x = 0;
		x += speed;
		change = true;
	}
	else dir = NOT_MOVING;
	eatPellet();
	return change;
}

bool HumanPlayer::moveUp() {
	bool change = false;
	if (map->getMapPos(getTileX(), (tileHeight + (getTileY() - 1) % tileHeight) % tileHeight) == 0 || getTileOffsetY() > 0) {
		if (y <= 0) y = height;
		y -= speed;
		change = true;
	}
	else dir = NOT_MOVING;
	eatPellet();
	return change;
}

bool HumanPlayer::moveDown() {
	bool change = false;
	if (map->getMapPos(getTileX(), (tileHeight + (getTileY() + 1) % tileHeight) % tileHeight) == 0 || getTileOffsetY() < 0) {
		if (y >= height) y = 0;
		y += speed;
		 change = true;
	}
	else dir = NOT_MOVING;
	eatPellet();
	return change;
}

void HumanPlayer::changeDirection(int newDirection) {
	bool snapNeeded = ((dir == LEFT || dir == RIGHT) == (newDirection == UP || newDirection == DOWN));

	switch (newDirection) {
	case UP:
		if (map->getMapPos(getTileX(), (tileHeight + (getTileY() - 1) % tileHeight) % tileHeight) == 0) {
			dir = newDirection;
			if (snapNeeded) snapTileX();
		}
		break;
	case DOWN:
		if (map->getMapPos(getTileX(), (tileHeight + (getTileY() + 1) % tileHeight) % tileHeight) == 0) {
			dir = newDirection;
			if (snapNeeded) snapTileX();
		}
		break;
	case LEFT:
		if (map->getMapPos((tileWidth + (getTileX() - 1) % tileWidth) % tileWidth, getTileY()) == 0) {
			dir = newDirection;
			if (snapNeeded) snapTileY();
		}
		break;
	case RIGHT:
		if (map->getMapPos((tileWidth + (getTileX() + 1) % tileWidth) % tileWidth, getTileY()) == 0) {
			dir = newDirection;
			if (snapNeeded) snapTileY();
		}
		break;
	}
	return;
}

int HumanPlayer::getScore() {
	return score;
}

void HumanPlayer::eatPellet() {
	if (map->getObjectPos(getTileX(), getTileY()) == 1) {
		map->eatObject(getTileX(), getTileY());
		score += 10;
	}
	else if (map->getObjectPos(getTileX(), getTileY()) == 2) {
		map->eatObject(getTileX(), getTileY());
		state = 300;
		eq->push(new Event(1));
	}
	else if (map->getObjectPos(getTileX(), getTileY()) == 4) {
		map->eatObject(getTileX(), getTileY());
		score += 30;
		eq->push(new Event(2));
	}
}

int HumanPlayer::getPosX() {
	return getTileX() * tileSize + getTileOffsetX();
}

int HumanPlayer::getPosY() {
	return getTileY() * tileSize + getTileOffsetY();
}

void HumanPlayer::ghostCollision(int ghostState) {
	if (ghostState == 0 && state == 0) alive = false;
	if (ghostState == 1 && state != 0) score += 100;
}

bool HumanPlayer::isAlive() {
	return alive;
}

bool HumanPlayer::isBig() {
	return state != 0;
}

void HumanPlayer::die() {
	alive = false;
	dir = NOT_MOVING;
}