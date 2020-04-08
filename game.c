#include "game.h"

#include "global.h"
#include "tetromino.h"

#include <stdlib.h>
#include <time.h>

tetromino gTetro;

void init(){
    SDL_Init(SDL_INIT_VIDEO|SDL_INIT_JOYSTICK);
    SDL_DisplayMode DM;
    if(SDL_GetCurrentDisplayMode(0, &DM) != 0){
        return;
    }
    WINDOW_WIDTH = DM.w;
    WINDOW_HEIGHT = DM.h;
    window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_FULLSCREEN);
    render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    TILE_SIZE = WINDOW_HEIGHT/24;
    START_SCREEN = (WINDOW_WIDTH-TILE_SIZE*10)/2;
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 24; j++){
            world[i][j] = 0;
        }
    }
    srand(time(0));
    resetT(&gTetro);
    gameOver = 0;
}

void updateLogic(){
    input_t(&gTetro);
    updateLogic_t(&gTetro);
    int findLine = -1;
    for(int j = 23; j >= 0 && findLine == -1; j--){
        int completeLine = 0;
        for(int i = 0; i < 10; i++){
            if(world[i][j]) completeLine++;
        }
        if(completeLine == 10){
            findLine = j;
        }
    }
    for(int j = findLine; j > 0; j--){
        for(int i = 0; i < 10; i++){
            world[i][j] = world[i][j-1];
        }
    }
}

void renderScene(){
    SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
    SDL_RenderClear(render);
    SDL_Rect background = {START_SCREEN, 0, 10*TILE_SIZE, 24*TILE_SIZE};
    SDL_SetRenderDrawColor(render, 20, 20, 20, 255);
    SDL_RenderFillRect(render, &background);
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 24; j++){
            if(!world[i][j]) continue;
            if(world[i][j] == STRAIGHT_T) SDL_SetRenderDrawColor(render, 66, 209, 245, 255);
            if(world[i][j] == SQUARE_T) SDL_SetRenderDrawColor(render, 246, 250, 7, 255);
            if(world[i][j] == TPOL_T) SDL_SetRenderDrawColor(render, 250, 7, 238, 255);
            if(world[i][j] == LPOL_T) SDL_SetRenderDrawColor(render, 240, 155, 36, 255);
            if(world[i][j] == SPOL_T) SDL_SetRenderDrawColor(render, 36, 240, 39, 255);
            if(world[i][j] == LPOL2_T) SDL_SetRenderDrawColor(render, 22, 18, 227, 255);
            if(world[i][j] == SPOL2_T) SDL_SetRenderDrawColor(render, 245, 42, 42, 255);
            SDL_Rect box = {START_SCREEN+TILE_SIZE*i, TILE_SIZE*j, TILE_SIZE, TILE_SIZE};
            SDL_RenderFillRect(render, &box);
        }
    }
    render_t(&gTetro);
    SDL_RenderPresent(render);
}

void gameLoop(){
    int quit = 0;
    SDL_Event e;
    while(!quit){
        Uint32 firstTime = SDL_GetTicks();
        while(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT) quit = 1;
        }
        updateLogic();
        renderScene();
        deltaTime = (double)(SDL_GetTicks()-firstTime)/1000;
        if(gameOver){
            for(int i = 0; i < 10; i++){
                for(int j = 0; j < 24; j++){
                    world[i][j] = 0;
                }
            }
            gameOver = 0;
        }
    }
}

void game(){
    init();
    gameLoop();
    close();
}

void close(){
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
}
