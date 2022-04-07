#ifndef DRAW_H
#define DRAW_H

#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <vector>
#include <string>

#include "../Game/PlayerInfo.h"

using namespace std;

const float PI = 3.1415927;
enum DIRECTION { RIGHT, DOWN, LEFT, UP, NOT_MOVING };

class Draw {
public:
	static Draw* instance();
	void static generateGhostColor(int& r, int& g, int& b, int hue);
	void static generatePlayerColor(int& r, int& g, int& b, int hue);
	void initializeProportions(int w, int h);
	void initializeMapProportions(int tileW, int tileH);
	void drawGhost(int x, int y, int dir, int r, int g, int b);
	void drawPlayer(int x, int y, int dir, int frame, int r, int g, int b);
	void drawBigPlayer(int x, int y, int dir, int frame, int r, int g, int b);
	void drawShrinkingPlayer(int x, int y, int dir, int frame, int r, int g, int b, int size);
	void drawDyingPlayer(int x, int y, int dir, int frame, int r, int g, int b);
	void drawMap(int** map, int** object, int frame, int h, int w);
	void drawScore(int score, int player, int totalPlayers, PlayerInfo* p);
	int getTileSize();
	int getTileWidth();
	int getTileHeight();
	int getHeight();
	int getWidth();

	void drawMenu(int frame);
	void drawLevelSelect(std::vector<std::string> levels, int selected);
	void drawScoreboard(std::vector<PlayerInfo*> players, int selected);
	void drawSettings(int numGhosts, int numPlayers, std::string gameMode, int selected);
	void drawCharacterSelect(std::vector<PlayerInfo*> players, int offset, std::vector<std::string> nameOptions);

	void highlightTile(int x, int y);
protected:
	Draw();
private:
	static Draw* _instance;
	static void hsv_to_rgb(double& h, double& s, double& v);
	void drawGlowingLine(float x1, float y1, float x2, float y2, ALLEGRO_COLOR color, float glowThickness, int vibrance);
	void drawGlowingWall(float x1, float y1, float x2, float y2, ALLEGRO_COLOR color, float thickness);
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
	void drawGlow(int x, int y, int r, int g, int b, int radius, int vibrance);
	void drawCherry(int x, int y);
	void drawPellet(int x, int y);
	void drawPowerup(int x, int y, int frame);
	void drawCharacter(PlayerInfo* player, float x1, float y1, float x2, float y2, std::vector<std::string> nameOptions);
	double corner;
	int thickness;
	void initializeTileSize();
	ALLEGRO_FONT *font;
	ALLEGRO_BITMAP* menu;
	ALLEGRO_FONT* titleFont;
	ALLEGRO_FONT* menuFont;
	ALLEGRO_FONT* characterFont;
};

#endif