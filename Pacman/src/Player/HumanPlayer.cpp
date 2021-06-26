#include "HumanPlayer.h"
#include "States/PlayerState.h"
#include "../Graphics/Audio/Audio.h"

using namespace std;

HumanPlayer::HumanPlayer(Map* m, int startX, int startY, int red, int green, int blue) {
	eq = eq->getInstance();
	Draw* draw = Draw::instance();
	tileSize = draw->getTileSize();
	tileWidth = draw->getTileWidth();
	tileHeight = draw->getTileHeight();
	height = tileHeight * tileSize;
	width = tileWidth * tileSize;
	state = new PlayerState(this);

	map = m;
	x = startX * tileSize + (tileSize / 2);
	y = startY * tileSize + (tileSize / 2);
	dir = NOT_MOVING;
	score = 0;
	r = red;
	g = green;
	b = blue;

	return;
}

HumanPlayer::~HumanPlayer() {
	delete state;
	return;
}

bool HumanPlayer::update() {
	bool stateUpdate = state->update();
	if (!state->canMove()) dir = NOT_MOVING;
	switch (dir) {
	case NOT_MOVING:
		return stateUpdate;
	case UP:
		return moveUp() || stateUpdate;
	case DOWN:
		return moveDown() || stateUpdate;
	case LEFT:
		return moveLeft() || stateUpdate;
	case RIGHT:
		return moveRight() || stateUpdate;
	default:
		return stateUpdate;
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
	state->draw(x, y, dir, r, g, b);
	return;
}

bool HumanPlayer::moveLeft() {
	bool change = false;
	if (map->getMapPos((tileWidth + (getTileX() - 1) % tileWidth) % tileWidth, getTileY()) == 0 || getTileOffsetX() > 0) {
		if (x <= 0)x = width;
		x -= state->getSpeed();
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
		x += state->getSpeed();
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
		y -= state->getSpeed();
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
		y += state->getSpeed();
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
		Audio::instance()->chomp();
	}
	else if (map->getObjectPos(getTileX(), getTileY()) == 2) {
		map->eatObject(getTileX(), getTileY());
		state->powerUp();
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
	if (ghostState == 1) score += 100;
	state->ghostCollision(ghostState);
}

bool HumanPlayer::isAlive() {
	return state->isAlive();
}

bool HumanPlayer::isBig() {
	return state->isBig();
}

void HumanPlayer::die() {
	state->die();
}

void HumanPlayer::changeState(PlayerState* newState) {
	delete state;
	state = newState;
}