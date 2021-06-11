#include "BuilderMap.h"
#include <sstream>
#include <fstream>
#include <iostream>

using namespace std;

BuilderMap::BuilderMap(int h, int w, int options, string level) {
	pellets = 0.0;
	pelletsEaten = 0.0;
	option = -1;
	lastHouseCoord = -1;
	lastSpawnCoord = -1;
    STATE state = MAP;
    curObj = 0;
    frame = 0;
    quit = false;
    filename = level;

	width = w;
    height = h;
    numOptions = options;

    selectX = 0;
    selectY = 0;

	Draw::instance()->initializeMapProportions(width, height);

	map = new int*[height];
	object = new int*[height];
	spawns = new int*[height];

	for (int i = 0; i < height; i++) {
		map[i] = new int[width];
		object[i] = new int[width];
		spawns[i] = new int[width];
	}

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
            if (x == 0 || y == 0 || x == width - 1 || y == height - 1) map[y][x] = 1;
			else map[y][x] = 0;
            object[y][x] = 0;
            spawns[y][x] = 0;
		}
	}


	objectOptions = new int**[numOptions];
	for (int i = 0; i < numOptions; i++) {
		objectOptions[i] = new int*[height];
		for (int j = 0; j < height; j++) {
			objectOptions[i][j] = new int[width];
		}
	}

	return;
}

BuilderMap::~BuilderMap() {
	for (int i = 0; i < height; i++) {
		delete map[i];
		delete object[i];
		delete spawns[i];
	}
   
	delete map;
	delete object;
	delete spawns;

	for (int i = 0; i < numOptions; i++) {
		for (int j = 0; j < height; j++) {
			delete objectOptions[i][j];
		}
		delete objectOptions[i];
	}
	delete objectOptions;

	return;
}

int BuilderMap::getMapPos(int x, int y) {
	return map[y][x];
}

int BuilderMap::getObjectPos(int x, int y) {
	return object[y][x];
}

void BuilderMap::eatObject(int x, int y) {
	if (object[y][x] == 1) pelletsEaten++;
	object[y][x] = 0;
}

bool BuilderMap::run(ALLEGRO_EVENT events) {
    if (events.type == ALLEGRO_EVENT_KEY_DOWN) {
		switch (events.keyboard.keycode) {
		case ALLEGRO_KEY_UP:
            if (selectY <= 0) selectY = height - 1;
			else --selectY;
			break;
		case ALLEGRO_KEY_LEFT:
            if(selectX <= 0) selectX = width - 1;
			else --selectX;
			break;
		case ALLEGRO_KEY_DOWN:
			selectY = ++selectY % height;
			break;
		case ALLEGRO_KEY_RIGHT:
			selectX = ++selectX % width;
			break;
        case ALLEGRO_KEY_0:
            setMap(0);
            break;
        case ALLEGRO_KEY_1:
            setMap(1);
            break;
        case ALLEGRO_KEY_2:
            setMap(2);
            break;
        case ALLEGRO_KEY_3:
            setMap(3);
            break;
        case ALLEGRO_KEY_ENTER:
            next();
            break;
		case ALLEGRO_KEY_ESCAPE:
			return true;
		}
	}
    else if (update()) {
        draw();
    }

    return quit;
}

void BuilderMap::setMap(int val) {
    if (state == MAP) map[selectY][selectX] = val;
    else if (state == OBJ && val < 3) object[selectY][selectX] = val;
    else if (state == CHERRY && val == 0) object[selectY][selectX] = val;
    else if (state == CHERRY && val == 1) object[selectY][selectX] = 4;
    else if (state == SPAWN && val < 2) spawns[selectY][selectX] = val;
    return;
}

void BuilderMap::next() {
    if (state == MAP) state = OBJ;
    else if (state == OBJ) {
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                objectOptions[curObj][y][x] = object[y][x];
                object[y][x] = 0;
            }
        }

        curObj++;
        if (curObj >= numOptions) state = CHERRY;
    }
    else if (state == CHERRY) {
        state = SPAWN;
    }
    else {
        writeFile();
    }
    
    return;
}

bool BuilderMap::update() {
	frame = (++frame) % 30;
	return frame % 5 == 0;
}

void BuilderMap::draw() {
    al_clear_to_color(al_map_rgb(0, 0, 0));
	Draw* draw = Draw::instance();
	draw->drawMap(map, object, frame, height, width);
    draw->highlightTile(selectX, selectY);
    int tileSize = draw->getTileSize();

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (spawns[y][x] == 1) draw->drawPlayer(x * tileSize + (tileSize / 2), y * tileSize + (tileSize / 2), 0, frame, 255, 255, 0);
        }
    }

    al_flip_display();
	return;
}

void BuilderMap::getHouseCoordinates(int &coordX, int &coordY) {
	lastHouseCoord = (lastHouseCoord + 1) % houseCoords.size();
	coordX = houseCoords.at(lastHouseCoord)->x;
	coordY = houseCoords.at(lastHouseCoord)->y;
	return;
}

void BuilderMap::getHouseGate(int &coordX, int &coordY) {
	coordX = houseCoords.at(0)->x;
	coordY = houseCoords.at(0)->y;
	return;
}

void BuilderMap::getPlayerSpawnCoordinates(int& x, int& y) {
	lastSpawnCoord = (lastSpawnCoord + 1) % playerSpawnCoords.size();
	x = playerSpawnCoords.at(lastSpawnCoord)->x;
	y = playerSpawnCoords.at(lastSpawnCoord)->y;
	return;
}

double BuilderMap::getPelletPercent() {
	return pelletsEaten / pellets;
}

void BuilderMap::switchObjectMap() {
	fruitOut = false;
	option = (option + 1) % numOptions;
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			object[y][x] = objectOptions[option][y][x];
			if (object[y][x] == 1) pellets++;
		}
	}
}

int BuilderMap::getHeight() {
	return height;
}

int BuilderMap::getWidth() {
	return width;
}

void BuilderMap::writeFile() {
    ofstream file(filename + ".pac");
    file << height << " " << width << endl;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width - 1; x++) {
            file << map[y][x] << " ";
        }
        file << map[y][width - 1] << endl;
    }

    file << numOptions << endl;

    for (int z = 0; z < numOptions; z++) {
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width - 1; x++) {
                file << objectOptions[z][y][x] << " ";
            }
            file << objectOptions[z][y][width - 1] << endl;
        }
    }

    int count = 0;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (spawns[y][x]) count++;
        }
    }

    file << count << endl;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (spawns[y][x]) file << x << " " << y << endl;
        }
    }

    count = 0;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (object[y][x]) count++;
        }
    }

    file << count << endl;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (object[y][x]) file << x << " " << y << endl;
        }
    }

    file.close();
    quit = true;
    return;
}