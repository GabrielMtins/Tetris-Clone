#ifndef GLOBAL_H
#define GLOBAL_H

#include <SDL2/SDL.h>

SDL_Window* window;
SDL_Renderer* render;

#define STRAIGHT_T 1
#define SQUARE_T 2
#define TPOL_T 3
#define LPOL_T 4
#define SPOL_T 5
#define LPOL2_T 6
#define SPOL2_T 7

double deltaTime;

int gameOver;

int WINDOW_WIDTH, WINDOW_HEIGHT;

int TILE_SIZE, START_SCREEN;

int world[10][24];

#endif
