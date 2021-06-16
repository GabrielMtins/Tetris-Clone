#ifndef GLOBAL_H
#define GLOBAL_H

#include <SDL2/SDL.h>

extern SDL_Window* window;
extern SDL_Renderer* render;

#define STRAIGHT_T 1
#define SQUARE_T 2
#define TPOL_T 3
#define LPOL_T 4
#define SPOL_T 5
#define LPOL2_T 6
#define SPOL2_T 7

extern double deltaTime;

extern int gameOver;

extern int WINDOW_WIDTH, WINDOW_HEIGHT;

extern int TILE_SIZE, START_SCREEN;

extern int world[10][24];

#endif
