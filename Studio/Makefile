src = $(wildcard *.cpp) \
	  $(wildcard ../Pacman/src/Graphics/*.cpp) \
	  $(wildcard ../Pacman/src/Map/*.cpp)

obj = $(src:.cpp=.o)

CC = g++
FLAGS = -lallegro -lallegro_main -lallegro_primitives -lallegro_color -lallegro_font -lallegro_ttf -lallegro_image -lallegro_audio -lallegro_acodec

Studio: $(obj)
	$(CC) -o $@ $^ $(FLAGS)

.PHONY: clean
clean:
	rm -f $(obj) Studio