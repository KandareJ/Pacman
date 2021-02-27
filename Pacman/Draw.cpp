#define _CRT_SECURE_NO_WARNINGS
#include "Draw.h"
#include <iostream>
#include <stdio.h>
#include <math.h>

using namespace std;

Draw* Draw::_instance = 0;

Draw* Draw::instance() {
	if (_instance == 0) {
		_instance = new Draw();
	}
	return _instance;
}

Draw::Draw() {
	initialized = false;
	return;
}

void Draw::initializeProportions(int w, int h) {
	width = w;
	height = h;
	titleFont = al_load_font("assets/fonts/SpaceObsessed.ttf", h / 7, NULL);
	menuFont = al_load_font("assets/fonts/SpaceObsessed.ttf", h / 15, NULL);
	menu = al_load_bitmap("assets/images/menu.png");
	return;
}

void Draw::initializeMapProportions(int tile_w, int tile_h) {
	tileWidth = tile_w;
	tileHeight = tile_h;
	initializeTileSize();
	return;
}

void Draw::initializeTileSize() {
	yOffset = height * .1;
	int maxWidth = width / tileWidth;
	int maxHeight = (height - yOffset) / tileHeight;

	tileSize = (maxWidth < maxHeight) ? maxWidth : maxHeight;
	xOffset = (width - tileSize * tileWidth) / 2;
	yOffsetScore = tileSize * tileHeight;
	yOffset = 0;
	corner = 0.1;
	thickness = 3;
	font = al_load_font("assets/fonts/SpaceObsessed.ttf", tileSize/2, NULL);
	initialized = true;
}

int Draw::getTileHeight() {
	return tileHeight;
}

int Draw::getTileWidth() {
	return tileWidth;
}

int Draw::getTileSize() {
	return tileSize;
}

int Draw::getHeight() {
	return height;
}

int Draw::getWidth() {
	return width;
}

void Draw::generateGhostColor(int& r, int& g, int& b, int hue) {
	double h = hue;
	if (h > 210) h += 60; //skip blue colors
	double s = 0.99;
	double v = 0.99;
	hsv_to_rgb(h, s, v);
	r = (int)h;
	g = (int)s;
	b = (int)v;
}

//we map h to r, s to g, and v to b
void Draw::hsv_to_rgb(double& h, double& s, double& v) {
	double r, g, b;
	double c = (v * s);
	int h_i = h / 60;
	double x = c * (1 - abs(fmod(h/60.0, 2) - 1));
	double m = v - c;

	switch (h_i) {
	case 0:
		r = c;
		g = x;
		b = 0;
		break;
	case 1:
		r = x;
		g = c;
		b = 0;
		break;
	case 2:
		r = 0;
		g = c;
		b = x;
		break;
	case 3:
		r = 0;
		g = x;
		b = c;
		break;
	case 4:
		r = x;
		g = 0;
		b = c;
		break;
	default:
		r = c;
		g = 0;
		b = x;
	};

	h = (r + m) * 255;
	s = (g + m) * 255;
	v = (b + m) * 255;
}

ALLEGRO_COLOR premul_alpha(ALLEGRO_COLOR color) {
    float r, g, b, a;
    al_unmap_rgba_f(color, &r, &g, &b, &a);
    return al_map_rgba_f(r * a, g * a, b * a, a);
}

void Draw::drawGlow(int x, int y, int r, int g, int b, int radius, int vibrance) {
	for (int size = tileSize / 2 + radius; size > tileSize / 2 - 50; size -= 5) {
		al_draw_filled_circle(x + xOffset, y + yOffset, size, premul_alpha(al_map_rgba(r, g, b, vibrance)));
	}
}

void Draw::drawGhost(int x, int y, int dir, int r, int g, int b) {
	if (!initialized) return;
	int third = tileSize * 0.15;

	if (r || g || b) drawGlow(x, y, r, g, b, 20, 10);

	if (r || g || b) {
		al_draw_filled_circle(x + xOffset, y - third + yOffset, 2 * third, al_map_rgb(r, g, b));
		al_draw_filled_rectangle(x - 2 * third + xOffset, y - third + yOffset, x + 2 * third + xOffset, y + 2 * third + yOffset, al_map_rgb(r, g, b));
	}
	//al_draw_filled_triangle(x - 12, y + 12, x - 6, y + 12, x - 9, y + 15, al_map_rgb(r, g, b));
	//al_draw_filled_triangle(x - 6, y + 12, x, y + 12, x - 3, y + 15, al_map_rgb(r, g, b));
	//al_draw_filled_triangle(x, y + 12, x + 6, y + 12, x + 3, y + 15, al_map_rgb(r, g, b));
	//al_draw_filled_triangle(x + 12, y + 12, x + 6, y + 12, x + 9, y + 15, al_map_rgb(r, g, b));
	al_draw_filled_circle(x - third + xOffset, y - third + yOffset, third*.66, al_map_rgb(255, 255, 255));
	al_draw_filled_circle(x + third + xOffset, y - third + yOffset, third*.66, al_map_rgb(255, 255, 255));

	int pupilOffset = .33 * third;

	switch (dir) {
	case UP:
		al_draw_filled_circle(x - third + xOffset, y - third - pupilOffset + yOffset, pupilOffset*1.5, al_map_rgb(0, 0, 0));
		al_draw_filled_circle(x + third + xOffset, y - third - pupilOffset + yOffset, pupilOffset*1.5, al_map_rgb(0, 0, 0));
		break;
	case DOWN:
		al_draw_filled_circle(x - third + xOffset, y - third + pupilOffset + yOffset, pupilOffset*1.5, al_map_rgb(0, 0, 0));
		al_draw_filled_circle(x + third + xOffset, y - third + pupilOffset + yOffset, pupilOffset*1.5, al_map_rgb(0, 0, 0));
		break;
	case RIGHT:
		al_draw_filled_circle(x - third + pupilOffset + xOffset, y - third + yOffset, pupilOffset*1.5, al_map_rgb(0, 0, 0));
		al_draw_filled_circle(x + third + pupilOffset + xOffset, y - third + yOffset, pupilOffset*1.5, al_map_rgb(0, 0, 0));
		break;
	case LEFT:
		al_draw_filled_circle(x - third - pupilOffset + xOffset, y - third + yOffset, pupilOffset*1.5, al_map_rgb(0, 0, 0));
		al_draw_filled_circle(x + third - pupilOffset + xOffset, y - third + yOffset, pupilOffset*1.5, al_map_rgb(0, 0, 0));
		break;
	default:
		al_draw_filled_circle(x - third + xOffset, y - third + yOffset, pupilOffset*1.5, al_map_rgb(0, 0, 0));
		al_draw_filled_circle(x + third + xOffset, y - third + yOffset, pupilOffset*1.5, al_map_rgb(0, 0, 0));
	};
}

void Draw::drawPlayer(int x, int y, int dir, int frame, int r, int g, int b, int state) {
	if (!initialized) return;

	if (r || g || b) (state) ? drawGlow(x, y, r, g, b, 45, 7) : drawGlow(x, y, r, g, b, 30, 7);

	int playerSize = (state) ? tileSize* 0.55 : tileSize * 0.40; // if state is not zero, pacman will be big
	float mouth = 1.5 / (frame + 1.0);
	if (frame >= 4.0)mouth = 1.0 / (8.0 - frame);
	float startTheta = (dir * .5 * PI) + mouth / 2.0;
	float deltaTheta = 2.0 * PI - mouth;
	al_draw_arc(x + xOffset, y + yOffset, playerSize / 2, startTheta, deltaTheta, al_map_rgb(r, g, b), playerSize);
	if (mouth == 0 || dir == NOT_MOVING) al_draw_arc(x + xOffset, y + yOffset, playerSize / 2, 0, 2 * PI, al_map_rgb(r, g, b), playerSize);
}

void Draw::drawMap(int **map, int **object, int frame, int h, int w) {
	if (!initialized) return;
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			// draw wall
			if (map[y][x] == 1) drawWalls(x, y, h, w, map);
			// draw ghost house gate
			else if (map[y][x] == 2) al_draw_line(x * tileSize - (tileSize*corner) + xOffset, y * tileSize + (tileSize*corner) + yOffset, (x + 1) * tileSize + (tileSize*corner) + xOffset, y * tileSize + (tileSize*corner) + yOffset, al_map_rgb(0, 0, 255), 3);
			//draw normal pellets
			if (object[y][x] == 1) al_draw_filled_circle(x * tileSize + (tileSize / 2) + xOffset, y * tileSize + (tileSize / 2) + yOffset, tileSize / 8, al_map_rgb(219, 133, 28));
			// draw power-up pellets that animate
			if (object[y][x] == 2) {
				if (frame < 15)al_draw_filled_circle(x * tileSize + (tileSize / 2) + xOffset, y * tileSize + (tileSize / 2) + yOffset, 7 + (frame / 7), al_map_rgb(80, 200, 28));
				else al_draw_filled_circle(x * tileSize + (tileSize / 2) + xOffset, y * tileSize + (tileSize / 2) + yOffset, 9 - ((frame - 14) / 7), al_map_rgb(80, 200, 28));
			}
			if (object[y][x] == 4) al_draw_filled_circle(x * tileSize + (tileSize / 2) + xOffset, y * tileSize + (tileSize / 2) + yOffset, tileSize / 8, al_map_rgb(255, 0, 255));
		}
	}
	return;
}

void Draw::drawWalls(int x, int y, int h, int w, int** map) {
	drawTopWall(x, y, w, h, map);
	drawBottomWall(x, y, w, h, map);
	drawLeftWall(x, y, w, h, map);
	drawRightWall(x, y, w, h, map);
	
	// bottom right corner
	if (map[y][x] == 1 && (x == w - 1 || map[y][x + 1] == 1) && (y == h - 1 || map[y + 1][x] == 1) && (x != w - 1 && y != h - 1 && map[y + 1][x + 1] != 1)) {
		al_draw_line((x + 1) * tileSize + xOffset, (y + 1)*tileSize - (tileSize*corner) + yOffset, (x + 1) * tileSize - (tileSize*corner) + xOffset, (y + 1) * tileSize - (tileSize*corner) + yOffset, al_map_rgb(0, 255, 255), thickness);
		al_draw_line((x + 1) * tileSize - (tileSize*corner) + xOffset, (y + 1)*tileSize - (tileSize*corner) + yOffset, (x + 1) * tileSize - (tileSize*corner) + xOffset, (y + 1) * tileSize + yOffset, al_map_rgb(0, 255, 255), thickness);
	}
	// bottom left corner
	if (map[y][x] == 1 && (x == 0 || map[y][x - 1] == 1) && (y==h-1||map[y + 1][x] == 1) && (x != 0 && y!=h-1 && map[y + 1][x - 1] != 1)) {
		al_draw_line((x) * tileSize + xOffset, (y + 1)*tileSize - (tileSize*corner) + yOffset, (x) * tileSize + (tileSize*corner) + xOffset, (y + 1) * tileSize - (tileSize*corner) + yOffset, al_map_rgb(0, 255, 255), thickness);
		al_draw_line((x) * tileSize + (tileSize*corner) + xOffset, (y + 1)*tileSize - (tileSize*corner) + yOffset, (x) * tileSize + (tileSize*corner) + xOffset, (y + 1) * tileSize + yOffset, al_map_rgb(0, 255, 255), thickness);
	}
	// top right corner
	if (map[y][x] == 1 && (x==w-1||map[y][x + 1] == 1) && (y!=0 && map[y - 1][x] == 1) && (y!=0 && x!=w-1 &&map[y - 1][x + 1] != 1)) {
		al_draw_line((x + 1) * tileSize + xOffset, (y)*tileSize + (tileSize*corner) + yOffset, (x + 1) * tileSize - (tileSize*corner) + xOffset, (y) * tileSize + (tileSize*corner) + yOffset, al_map_rgb(0, 255, 255), thickness);
		al_draw_line((x + 1) * tileSize - (tileSize*corner) + xOffset, (y)*tileSize + (tileSize*corner) + yOffset, (x + 1) * tileSize - (tileSize*corner) + xOffset, (y) * tileSize + yOffset, al_map_rgb(0, 255, 255), thickness);
	}
	// top left corner
	if (map[y][x] == 1 && (x==0||map[y][x - 1] == 1) && (y==0||map[y - 1][x] == 1) && (x!=0&&y!=0&&map[y - 1][x - 1] != 1)) {
		al_draw_line((x)* tileSize + xOffset, (y)*tileSize + (tileSize*corner) + yOffset, (x)* tileSize + (tileSize*corner) + xOffset, (y) * tileSize + (tileSize*corner) + yOffset, al_map_rgb(0, 255, 255), thickness);
		al_draw_line((x)* tileSize + (tileSize*corner) + xOffset, (y)*tileSize + (tileSize*corner) + yOffset, (x)* tileSize + (tileSize*corner) + xOffset, (y) * tileSize + yOffset, al_map_rgb(0, 255, 255), thickness);
	}
	
	return;
}

void Draw::drawTopWall(int x, int y, int w, int h, int** map) {
	if (y == 0 || map[y - 1][x] != 1) {
		if (x != 0 && map[y][x - 1] == 1)al_draw_line(x * tileSize + xOffset, y * tileSize + (tileSize*corner) + yOffset, x * tileSize + (tileSize*corner) + xOffset, y * tileSize + (tileSize*corner) + yOffset, al_map_rgb(0, 255, 255), thickness);
		if (map[y][x + 1] == 1)al_draw_line((x + 1) * tileSize - (tileSize*corner) + xOffset, y * tileSize + (tileSize*corner) + yOffset, (x + 1) * tileSize + xOffset, y * tileSize + (tileSize*corner) + yOffset, al_map_rgb(0, 255, 255), thickness);
		al_draw_line(x * tileSize + (tileSize*corner) + xOffset, y * tileSize + (tileSize*corner) + yOffset, (x + 1) * tileSize - (tileSize*corner) + xOffset, y * tileSize + (tileSize*corner) + yOffset, al_map_rgb(0, 255, 255), thickness);
	}
	return;
}

void Draw::drawBottomWall(int x, int y, int w, int h, int** map) {
	if (y == h - 1 || map[y + 1][x] != 1) {
		if (x != 0 && map[y][x - 1] == 1)al_draw_line(x * tileSize + xOffset, (y + 1) * tileSize - (tileSize*corner) + yOffset, x * tileSize + (tileSize*corner) + xOffset, (y + 1) * tileSize - (tileSize*corner) + yOffset, al_map_rgb(0, 255, 255), thickness);
		if (x != w - 1 && map[y][x + 1] == 1)al_draw_line((x + 1) * tileSize - (tileSize*corner) + xOffset, (y + 1) * tileSize - (tileSize*corner) + yOffset, (x + 1) * tileSize + xOffset, (y + 1) * tileSize - (tileSize*corner) + yOffset, al_map_rgb(0, 255, 255), thickness);
		al_draw_line(x * tileSize + (tileSize*corner) + xOffset, (y + 1) * tileSize - (tileSize*corner) + yOffset, (x + 1) * tileSize - (tileSize*corner) + xOffset, (y + 1) * tileSize - (tileSize*corner) + yOffset, al_map_rgb(0, 255, 255), thickness);
	}
	return;
}

void Draw::drawLeftWall(int x, int y, int w, int h, int** map) {
	if (x == 0 || map[y][x - 1] != 1) {
		if (y != 0 && map[y - 1][x] == 1)al_draw_line(x*tileSize + (tileSize*corner) + xOffset, y*tileSize + yOffset, x * tileSize + (tileSize*corner) + xOffset, y * tileSize + (tileSize*corner) + yOffset, al_map_rgb(0, 255, 255), thickness);
		if (y != h - 1 && map[y + 1][x] == 1)al_draw_line(x * tileSize + (tileSize*corner) + xOffset, (y + 1) * tileSize - (tileSize*corner) + yOffset, x * tileSize + (tileSize*corner) + xOffset, (y + 1) * tileSize + yOffset, al_map_rgb(0, 255, 255), thickness);
		al_draw_line(x * tileSize + (tileSize*corner) + xOffset, y * tileSize + (tileSize*corner) + yOffset, x * tileSize + (tileSize*corner) + xOffset, (y + 1) * tileSize - (tileSize*corner) + yOffset, al_map_rgb(0, 255, 255), thickness);
	}
	return;
}

void Draw::drawRightWall(int x, int y, int w, int h, int** map) {
	if (x == w - 1 || map[y][x + 1] != 1) {
		if (y != 0 && map[y - 1][x] == 1)al_draw_line((x + 1)*tileSize - (tileSize*corner) + xOffset, y*tileSize + yOffset, (x + 1) * tileSize - (tileSize*corner) + xOffset, y * tileSize + (tileSize*corner) + yOffset, al_map_rgb(0, 255, 255), thickness);
		if (y != h - 1 && map[y + 1][x] == 1)al_draw_line((x + 1) * tileSize - (tileSize*corner) + xOffset, (y + 1) * tileSize - (tileSize*corner) + yOffset, (x + 1) * tileSize - (tileSize*corner) + xOffset, (y + 1) * tileSize + yOffset, al_map_rgb(0, 255, 255), thickness);
		al_draw_line((x + 1) * tileSize - (tileSize*corner) + xOffset, y * tileSize + (tileSize*corner) + yOffset, (x + 1) * tileSize - (tileSize*corner) + xOffset, (y + 1) * tileSize - (tileSize*corner) + yOffset, al_map_rgb(0, 255, 255), thickness);
	}
	return;
}

void Draw::drawScore(int score, int player, int totalPlayers) {
	char *text = (char*)malloc(20);
	int col = (tileWidth - 3) * tileSize / 3;
	int row = player / 4 * tileSize / 2;
	sprintf(text, "Player %d: %d", player + 1, score);
	al_draw_text(font, al_map_rgb(255, 255, 255), (xOffset+tileSize*corner) + ((player % 4) * col), yOffsetScore + row, NULL, text);
	free(text);
}

void Draw::drawMenu(int frame) {
	if (menu) {
		int imageHeight = al_get_bitmap_height(menu);
		int imageWidth = al_get_bitmap_width(menu);
		al_draw_scaled_bitmap(menu, 0, 0, imageWidth, imageHeight, 0, 0, width, height, 0);
		int alpha = (frame < 45) ? frame * 255 / 45 : (45 - frame % 45) * 255 / 45;

		char title[8] = "PAC-MAN";
		char menuText[26] = "Press any key to continue";
		al_draw_text(titleFont, al_map_rgba(0, 0, 0, 255), width/2, height/2-(height/7*2), ALLEGRO_ALIGN_CENTRE, title);
		al_draw_text(menuFont, al_map_rgba(0, 0, 0, alpha), width / 2, height-(height/15*3), ALLEGRO_ALIGN_CENTRE, menuText);
	}
	return;
}

void Draw::drawLevelSelect(std::vector<std::string> levels, int selected) {
	if (menu) {
		int imageHeight = al_get_bitmap_height(menu);
		int imageWidth = al_get_bitmap_width(menu);
		int offset = 0;
		al_draw_scaled_bitmap(menu, 0, 0, imageWidth, imageHeight, 0, 0, width, height, 0);

		char title[14] = "Level Select:";
		al_draw_text(menuFont, al_map_rgb(0, 0, 0), width / 2, 0, ALLEGRO_ALIGN_CENTRE, title);
		al_draw_filled_rectangle(width * .25, height / 15 * 2, width * .75, height - height / 15 * 2 + height / 50, al_map_rgba(0, 0, 0, 190));

		if (selected >= 11) offset = (selected+1) % 11;
		for (unsigned int i = 0; i < levels.size() && i < 11; i++) {
			al_draw_text(menuFont, (i + offset == selected) ? al_map_rgb(255, 255, 255) : al_map_rgb(100, 100, 100) , width * .25 + height / 40, height / 15 * (2 + i), NULL, levels.at(i + offset).c_str());
		}
	}
	return;
}

void Draw::drawScoreboard(std::vector<int> scores, int selected) {
	if (menu) {
		int imageHeight = al_get_bitmap_height(menu);
		int imageWidth = al_get_bitmap_width(menu);
		int offset = 0;
		al_draw_scaled_bitmap(menu, 0, 0, imageWidth, imageHeight, 0, 0, width, height, 0);

		char title[14] = "Scoreboard:";
		al_draw_text(menuFont, al_map_rgb(0, 0, 0), width / 2, 0, ALLEGRO_ALIGN_CENTRE, title);
		al_draw_filled_rectangle(width * .25, height / 15 * 2, width * .75, height - height / 15 * 2 + height / 50, al_map_rgba(0, 0, 0, 190));

		if (selected >= 11) offset = (selected + 1) % 11;
		for (unsigned int i = 0; i < scores.size() && i < 11; i++) {
			char label[50];
			sprintf(label, "Player %d.........................%d", i + offset + 1, scores.at(i + offset));
			al_draw_text(menuFont, (i + offset == selected) ? al_map_rgb(255, 255, 255) : al_map_rgb(100, 100, 100), width * .25 + height / 40, height / 15 * (2 + i), NULL, label);
		}
	}
	return;
}