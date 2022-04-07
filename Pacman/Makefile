src = $(wildcard src/main.cpp) \
	  $(wildcard src/Events/*.cpp) \
	  $(wildcard src/Game/GameStates/*.cpp) \
	  $(wildcard src/Game/*.cpp) \
	  $(wildcard src/Ghost/States/*.cpp) \
	  $(wildcard src/Ghost/*.cpp) \
	  $(wildcard src/Graphics/*.cpp) \
	  $(wildcard src/Graphics/Audio/*.cpp) \
	  $(wildcard src/Map/*.cpp) \
	  $(wildcard src/Player/*.cpp) \
	  $(wildcard src/Player/States/*.cpp) \
	  $(wildcard src/Utils/*.cpp) \
	  $(wildcard src/Input/*.cpp) \
	  $(wildcard src/Drivers/*.cpp)

obj = $(src:.cpp=.o)

CC = g++
FLAGS = -lallegro -lallegro_main -lallegro_primitives -lallegro_color -lallegro_font -lallegro_ttf -lallegro_image -lallegro_audio -lallegro_acodec

PACMAN: $(obj)
	$(CC) -o $@ $^ $(FLAGS)

.PHONY: clean
clean:
	rm -f $(obj) PACMAN