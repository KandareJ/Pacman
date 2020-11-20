#ifndef DRAW_H
#define DRAW_H

#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <vector>

using namespace std;

const float PI = 3.1415927;
enum DIRECTION { RIGHT, DOWN, LEFT, UP, NOT_MOVING };

class Draw {
public:
	static Draw* instance();
	void initializeProportions(int w, int h);
	void initializeMapProportions(int tileW, int tileH);
	void drawGhost(int x, int y, int dir, int r, int g, int b);
	void drawPlayer(int x, int y, int dir, int frame, int r, int g, int b, int state);
	void drawMap(int** map, int** object, int frame, int h, int w);
	void drawScore(int score);
	int getTileSize();
	int getTileWidth();
	int getTileHeight();
	int getHeight();
	int getWidth();
protected:
	Draw();
private:
	static Draw* _instance;
	int width;
	int height;
	int tileWidth;
	int tileHeight;
	int tileSize;
	int xOffset;
	int yOffset;
	int yOffsetScore;
	bool initialized;
	void drawWalls(int x, int y, int h, int w, int** map);
	void drawTopWall(int x, int y, int w, int h, int**map);
	void drawBottomWall(int x, int y, int w, int h, int**map);
	void drawLeftWall(int x, int y, int w, int h, int**map);
	void drawRightWall(int x, int y, int w, int h, int**map);
	double corner;
	int thickness;
	void initializeTileSize();
	ALLEGRO_FONT *font;
};

#endif