# Pacman
Pacman is a multiplayer, battle royale style pacman game written in c++ and using Allegro 5.

## Setup
To run Pacman, you need to have Allegro 5 installed. Either download one of the binaries for your operating system [here](https://liballeg.org/), or build it yourself from this [repo](https://github.com/liballeg/allegro5).

Run the command `make` to compile Pacman.

## Levels
Pacman levels are loaded in dynammically from the levels directory. Levels can be built using the Studio. The Studio is more of a developer tool, however, and isn't very polished.

## Studio
The studio has its own makefile. Once it is built, run it and pass the level's desired height, weight, depth, and name as command line arguments. Move with the arrow keys to select a tile. Type 1, 2, or 3 over the selected tile to set its value. Pressing enter moves you to the next state. Each state has you build a different part of the level. The first state has you build the walls, the next has you place the pellets and powerups, the third has you place possible cherry spawns, and the final state has you place possible player spawns. Pressing enter while in the "spawn" state will save your file.
