#include "HumanPlayer.h"
#include "allegro5/allegro_primitives.h"
#include <iostream>

using namespace std;

const float PI = 3.1415927;

HumanPlayer::HumanPlayer(Map* m, int startX, int startY) {
	map = m;
	x = startX * 40 + 20;
	y = startY * 40 + 20;
	dir = NOT_MOVING;
	score = 0;
	speed = 5;
	frame = 0;
	return;
}

HumanPlayer::~HumanPlayer() {
	return;
}

bool HumanPlayer::update() {
	frame = ++frame % 8;
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
	return x / 40 % 20;
}

int HumanPlayer::getTileY() {

	int tile = y / 40 % 15;
	return tile;
}

void HumanPlayer::snapTileX() {
	x = (int)(x / 40) * 40 + 20;
}

void HumanPlayer::snapTileY() {
	y = (int)(y / 40) * 40 + 20;
}

int HumanPlayer::getTileOffsetX() {
	return (x - getTileX() * 40 - 20);
}
int HumanPlayer::getTileOffsetY() {
	return (y - getTileY() * 40 - 20);
}

void HumanPlayer::draw() {
	float mouth = 1.5/(frame+1.0);
	if (frame >= 4.0)mouth = 1.0 / (8.0 - frame);
	float startTheta = (dir * .5 * PI) + mouth / 2.0;
	float deltaTheta = 2.0 * PI - mouth;

	//al_draw_filled_circle(x, y, 18, al_map_rgb(255, 255, 0));
	al_draw_arc(x, y, 9, startTheta, deltaTheta, al_map_rgb(255, 255, 0), 18);
	if(mouth == 0 || dir == NOT_MOVING) al_draw_arc(x, y, 9, 0, 2*PI, al_map_rgb(255, 255, 0), 18);
	return;
}

bool HumanPlayer::moveLeft() {
	bool change = false;
	if (map->getMapPos((20 + (getTileX() - 1) % 20) % 20, getTileY()) == 0 || getTileOffsetX() > 0) {
		if (x <= 0)x = 800;
		x -= speed;
		change = true;
	}
	else dir = NOT_MOVING;
	if (map->getObjectPos(getTileX(), getTileY()) == 1) {
		score += 10;
		map->eatObject(getTileX(), getTileY());
	}
	return change;
}

bool HumanPlayer::moveRight() {
	bool change = false;
	if (map->getMapPos((20 + (getTileX() + 1) % 20) % 20, getTileY()) == 0 || getTileOffsetX() < 0) {
		if (x >= 800) x = 0;
		x += speed;
		change = true;
	}
	else dir = NOT_MOVING;
	if (map->getObjectPos(getTileX(), getTileY()) == 1) {
		map->eatObject(getTileX(), getTileY());
		score += 10;
	}
	return change;
}

bool HumanPlayer::moveUp() {
	bool change = false;
	if (map->getMapPos(getTileX(), (15 + (getTileY() - 1) % 15) % 15) == 0 || getTileOffsetY() > 0) {
		if (y <= 0) y = 600;
		y -= speed;
		change = true;
	}
	else dir = NOT_MOVING;
	if (map->getObjectPos(getTileX(), getTileY()) == 1) {
		map->eatObject(getTileX(), getTileY());
		score += 10;
	}
	return change;
}

bool HumanPlayer::moveDown() {
	bool change = false;
	if (map->getMapPos(getTileX(), (15 + (getTileY() + 1) % 15) % 15) == 0 || getTileOffsetY() < 0) {
		if (y >= 600) y = 0;
		y += speed;
		 change = true;
	}
	else dir = NOT_MOVING;
	if (map->getObjectPos(getTileX(), getTileY()) == 1) {
		map->eatObject(getTileX(), getTileY());
		score += 10;
	}
	return change;
}

void HumanPlayer::changeDirection(int newDirection) {
	bool snapNeeded = ((dir == LEFT || dir == RIGHT) == (newDirection == UP || newDirection == DOWN));

	switch (newDirection) {
	case UP:
		if (map->getMapPos(getTileX(), (15 + (getTileY() - 1) % 15) % 15) == 0) {
			dir = newDirection;
			if (snapNeeded) snapTileX();
		}
		break;
	case DOWN:
		if (map->getMapPos(getTileX(), (15 + (getTileY() + 1) % 15) % 15) == 0) {
			dir = newDirection;
			if (snapNeeded) snapTileX();
		}
		break;
	case LEFT:
		if (map->getMapPos((20 + (getTileX() - 1) % 20) % 20, getTileY()) == 0) {
			dir = newDirection;
			if (snapNeeded) snapTileY();
		}
		break;
	case RIGHT:
		if (map->getMapPos((20 + (getTileX() + 1) % 20) % 20, getTileY()) == 0) {
			dir = newDirection;
			if (snapNeeded) snapTileY();
		}
		break;
	}
	return;
}