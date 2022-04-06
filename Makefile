main:
	g++ -O3 -o main main.cpp  `sdl2-config --cflags --libs`  -lSDL2_image