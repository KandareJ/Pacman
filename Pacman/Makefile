src = $(wildcard src/main.cpp) \
	  $(wildcard src/Events/*.cpp) \
	  $(wildcard src/Game/GameStates/*.cpp) \
	  $(wildcard src/Game/*.cpp) \
	  $(wildcard src/Ghost/States/*.cpp) \
	  $(wildcard src/Ghost/*.cpp) \
	  $(wildcard src/Graphics/*.cpp) \
	  $(wildcard src/Map/*.cpp) \
	  $(wildcard src/Player/*.cpp)

obj = $(src:.cpp=.o)

CC = g++
FLAGS = -lallegro -lallegro_main -lallegro_primitives -lallegro_color -lallegro_font -lallegro_ttf -lallegro_image

PACMAN: $(obj)
	$(CC) -o $@ $^ $(FLAGS)

.PHONY: clean
clean:
	rm -f $(obj) PACMAN