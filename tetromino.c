#include "tetromino.h"

#include "global.h"

#include <stdio.h>
#include <stdlib.h>

#define ROTATION_ACTION 0
#define LEFT_ACTION -1
#define RIGHT_ACTION 1
#define NO_ACTION 2

double minLastTimeFall = 0.3;

/*
    left - 0
    up - 1
    right - 2
    down - 3
*/

void input_t(tetromino* t){
    Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
    if(currentKeyStates[SDL_SCANCODE_A]) t->currentAction = LEFT_ACTION;
    if(currentKeyStates[SDL_SCANCODE_D]) t->currentAction = RIGHT_ACTION;
    if(currentKeyStates[SDL_SCANCODE_E]) t->currentAction = ROTATION_ACTION;
    if(currentKeyStates[SDL_SCANCODE_S]) minLastTimeFall = 0.05;
}

int checkCollision_t(tetromino* t){
    if(t->type == STRAIGHT_T){
        if(t->rotation == 0 || t->rotation == 2){
            if(t->y < 0 || t->y >= 24 || t->x < 0 || t->x+3 >= 10) return 1;
            if(world[t->x][t->y] || world[t->x+1][t->y] || world[t->x+2][t->y] || world[t->x+3][t->y]) return 1;
        }
        else{
            if(t->x < 0 || t->x >= 10 || t->y < 0 || t->y+3 >= 24) return 1;
            if(world[t->x][t->y] || world[t->x][t->y+1] || world[t->x][t->y+2] || world[t->x][t->y+3]) return 1;
        }
    }
    if(t->type == SQUARE_T){
        if(t->x < 0 || t->x+1 >= 10 || t->y < 0 || t->y+1 >= 24) return 1;
        if(world[t->x][t->y] || world[t->x][t->y+1] || world[t->x+1][t->y] || world[t->x+1][t->y+1]) return 1;
    }
    if(t->type == TPOL_T){
        if(t->rotation == 0){
            if(t->x+2 >= 10 || t->x < 0 || t->y+1 >= 24 || t->y < 0) return 1;
            if(world[t->x+1][t->y+1] || world[t->x][t->y+1] || world[t->x+2][t->y+1] || world[t->x+1][t->y]) return 1;
        }
        if(t->rotation == 1){
            if(t->x+1 >= 10 || t->x < 0 || t->y < 0 || t->y+2 >= 24) return 1;
            if(world[t->x+1][t->y+1] || world[t->x][t->y+1] || world[t->x+1][t->y] || world[t->x+1][t->y+2]) return 1;
        }
        if(t->rotation == 2){
            if(t->x+2 >= 10 || t->x < 0 || t->y+2 >= 24 || t->y+1 < 0) return 1;
            if(world[t->x+1][t->y+1] || world[t->x][t->y+1] || world[t->x+2][t->y+1] || world[t->x+1][t->y+2]) return 1;
        }
        if(t->rotation == 3){
            if(t->x+2 >= 10 || t->x+1 < 0 || t->y < 0 || t->y+2 >= 24) return 1;
            if(world[t->x+1][t->y+1] || world[t->x+2][t->y+1] || world[t->x+1][t->y] || world[t->x+1][t->y+2]) return 1;
        }
    }
    if(t->type == LPOL_T){
        if(t->rotation == 0){
            if(t->x < 0 || t->x+1 >= 10 || t->y < 0 || t->y+2 >= 24) return 1;
            if(world[t->x][t->y] || world[t->x][t->y+1] || world[t->x][t->y+2] || world[t->x+1][t->y+2]) return 1;
        }
        if(t->rotation == 1){
            if(t->x < 0 || t->x+2 >= 10 || t->y < 0 || t->y+1 >= 24) return 1;
            if(world[t->x][t->y+1] || world[t->x+1][t->y+1] || world[t->x+2][t->y+1] || world[t->x+2][t->y]) return 1;
        }
        if(t->rotation == 2){
            if(t->x < 0 || t->x+1 >= 10 || t->y < 0 || t->y+2 >= 24) return 1;
            if(world[t->x+1][t->y] || world[t->x+1][t->y+1] || world[t->x+1][t->y+2] || world[t->x][t->y]) return 1;
        }
        if(t->rotation == 3){
            if(t->x < 0 || t->x+2 >= 10 || t->y+1 < 0 || t->y+2 >= 24) return 1;
            if(world[t->x][t->y+1] || world[t->x+1][t->y+1] || world[t->x+2][t->y+1] || world[t->x][t->y+2]) return 1;
        }
    }
    if(t->type == SPOL_T){
        if(t->rotation == 0 || t->rotation == 2){
            if(t->x < 0 || t->x+1 >= 10 || t->y < 0 || t->y+2 >= 24) return 1;
            if(world[t->x][t->y] || world[t->x][t->y+1] || world[t->x+1][t->y+1] || world[t->x+1][t->y+2]) return 1;
        }
        if(t->rotation == 1 || t->rotation == 3){
            if(t->x < 0 || t->x+2 >= 10 || t->y < 0 || t->y+1 >= 24) return 1;
            if(world[t->x][t->y+1] || world[t->x+1][t->y+1] || world[t->x+1][t->y] || world[t->x+2][t->y]) return 1;
        }
    }
    if(t->type == LPOL2_T){
        if(t->rotation == 0){
            if(t->x < 0 || t->x+1 >= 10 || t->y < 0 || t->y+2 >= 24) return 1;
            if(world[t->x+1][t->y] || world[t->x+1][t->y+1] || world[t->x+1][t->y+2] || world[t->x][t->y+2]) return 1;
        }
        if(t->rotation == 1){
            if(t->x < 0 || t->x+2 >= 10 || t->y < 0 || t->y+1 >= 24) return 1;
            if(world[t->x+2][t->y+1] || world[t->x][t->y] || world[t->x+1][t->y] || world[t->x+2][t->y]) return 1;
        }
        if(t->rotation == 2){
            if(t->x < 0 || t->x+1 >= 10 || t->y < 0 || t->y+2 >= 24) return 1;
            if(world[t->x+1][t->y] || world[t->x][t->y] || world[t->x][t->y+1] || world[t->x][t->y+2]) return 1;
        }
        if(t->rotation == 3){
            if(t->x < 0 || t->x+2 >= 10 || t->y < 0 || t->y+1 >= 24) return 1;
            if(world[t->x][t->y] || world[t->x][t->y+1] || world[t->x+1][t->y+1] || world[t->x+2][t->y+1]) return 1;
        }
    }
    if(t->type == SPOL2_T){
        if(t->rotation == 0 || t->rotation == 2){
            if(t->x < 0 || t->x+1 >= 10 || t->y < 0 || t->y+2 >= 24) return 1;
            if(world[t->x+1][t->y] || world[t->x+1][t->y+1] || world[t->x][t->y+1] || world[t->x][t->y+2]) return 1;
        }
        if(t->rotation == 1 || t->rotation == 3){
            if(t->x < 0 || t->x+2 >= 10 || t->y < 0 || t->y+1 >= 24) return 1;
            if(world[t->x][t->y] || world[t->x+1][t->y] || world[t->x+1][t->y+1] || world[t->x+2][t->y+1]) return 1;
         }
    }
    return 0;
}

void resetT(tetromino* t){
    if(t->type == STRAIGHT_T){
        if(t->rotation == 0 || t->rotation == 2){
            world[t->x][t->y] = STRAIGHT_T;
            world[t->x+1][t->y] = STRAIGHT_T;
            world[t->x+2][t->y] = STRAIGHT_T;
            world[t->x+3][t->y] = STRAIGHT_T;
        }
        else{
            world[t->x][t->y] = STRAIGHT_T;
            world[t->x][t->y+1] = STRAIGHT_T;
            world[t->x][t->y+2] = STRAIGHT_T;
            world[t->x][t->y+3] = STRAIGHT_T;
        }
    }
    if(t->type == SQUARE_T){
        world[t->x][t->y] = SQUARE_T;
        world[t->x][t->y+1] = SQUARE_T;
        world[t->x+1][t->y] = SQUARE_T;
        world[t->x+1][t->y+1] = SQUARE_T;
    }
    if(t->type == TPOL_T){
        if(t->rotation == 0){
            world[t->x+1][t->y+1] = TPOL_T;
            world[t->x+2][t->y+1] = TPOL_T;
            world[t->x+1][t->y] = TPOL_T;
            world[t->x][t->y+1] = TPOL_T;
        }
        if(t->rotation == 1){
            world[t->x+1][t->y+1] = TPOL_T;
            world[t->x+1][t->y+2] = TPOL_T;
            world[t->x+1][t->y] = TPOL_T;
            world[t->x][t->y+1] = TPOL_T;
        }
        if(t->rotation == 2){
            world[t->x][t->y+1] = TPOL_T;
            world[t->x+1][t->y+1] = TPOL_T;
            world[t->x+2][t->y+1] = TPOL_T;
            world[t->x+1][t->y+2] = TPOL_T;
        }
        if(t->rotation == 3){
            world[t->x+1][t->y+1] = TPOL_T;
            world[t->x+1][t->y] = TPOL_T;
            world[t->x+1][t->y+2] = TPOL_T;
            world[t->x+2][t->y+1] = TPOL_T;
        }
    }
    if(t->type == LPOL_T){
        if(t->rotation == 0){
            world[t->x][t->y] = LPOL_T;
            world[t->x][t->y+1] = LPOL_T;
            world[t->x][t->y+2] = LPOL_T;
            world[t->x+1][t->y+2] = LPOL_T;
        }
        if(t->rotation == 1){
            world[t->x][t->y+1] = LPOL_T;
            world[t->x+1][t->y+1] = LPOL_T;
            world[t->x+2][t->y+1] = LPOL_T;
            world[t->x+2][t->y] = LPOL_T;
        }
        if(t->rotation == 2){
            world[t->x+1][t->y] = LPOL_T;
            world[t->x+1][t->y+1] = LPOL_T;
            world[t->x+1][t->y+2] = LPOL_T;
            world[t->x][t->y] = LPOL_T;
        }
        if(t->rotation == 3){
            world[t->x][t->y+1] = LPOL_T;
            world[t->x+1][t->y+1] = LPOL_T;
            world[t->x+2][t->y+1] = LPOL_T;
            world[t->x][t->y+2] = LPOL_T;
        }
    }
    if(t->type == SPOL_T){
        if(t->rotation == 0 || t->rotation == 2){
            world[t->x][t->y] = SPOL_T;
            world[t->x][t->y+1] = SPOL_T;
            world[t->x+1][t->y+1] = SPOL_T;
            world[t->x+1][t->y+2] = SPOL_T;
        }
        if(t->rotation == 1 || t->rotation == 3){
            world[t->x][t->y+1] = SPOL_T;
            world[t->x+1][t->y+1] = SPOL_T;
            world[t->x+1][t->y] = SPOL_T;
            world[t->x+2][t->y] = SPOL_T;
        }
    }
    if(t->type == LPOL2_T){
        if(t->rotation == 0){
            world[t->x+1][t->y] = LPOL2_T;
            world[t->x+1][t->y+1] = LPOL2_T;
            world[t->x+1][t->y+2] = LPOL2_T;
            world[t->x][t->y+2] = LPOL2_T;
        }
        if(t->rotation == 1){
            world[t->x][t->y] = LPOL2_T;
            world[t->x+1][t->y] = LPOL2_T;
            world[t->x+2][t->y] = LPOL2_T;
            world[t->x+2][t->y+1] = LPOL2_T;
        }
        if(t->rotation == 2){
            world[t->x+1][t->y] = LPOL2_T;
            world[t->x][t->y] = LPOL2_T;
            world[t->x][t->y+1] = LPOL2_T;
            world[t->x][t->y+2] = LPOL2_T;
        }
        if(t->rotation == 3){
            world[t->x][t->y] = LPOL2_T;
            world[t->x][t->y+1] = LPOL2_T;
            world[t->x+1][t->y+1] = LPOL2_T;
            world[t->x+2][t->y+1] = LPOL2_T;
        }
    }
    if(t->type == SPOL2_T){
        if(t->rotation == 0 || t->rotation == 2){
            world[t->x+1][t->y] = SPOL2_T;
            world[t->x+1][t->y+1] = SPOL2_T;
            world[t->x][t->y+1] = SPOL2_T;
            world[t->x][t->y+2] = SPOL2_T;
        }
        if(t->rotation == 1 || t->rotation == 3){
            world[t->x][t->y] = SPOL2_T;
            world[t->x+1][t->y] = SPOL2_T;
            world[t->x+1][t->y+1] = SPOL2_T;
            world[t->x+2][t->y+1] = SPOL2_T;
        }
    }
    t->x = 5;
    t->y = 0;
    t->type = rand()%7+1;
    t->rotation = rand()%4;
    if(checkCollision_t(t)) gameOver = 1;

}

void updateLogic_t(tetromino* t){
    if(t->lastTimeAction >= 0.05){
        if(t->currentAction == LEFT_ACTION){
            t->x--;
            if(checkCollision_t(t)) t->x++;
        }
        if(t->currentAction == RIGHT_ACTION){
            t->x++;
            if(checkCollision_t(t)) t->x--;
        }
        t->lastTimeAction = 0;
    }
    if(t->lastTimeRotation >= 0.3 && t->currentAction == ROTATION_ACTION){
        t->rotation = (t->rotation+1)%4;
        if(checkCollision_t(t)) t->rotation--;
        if(t->rotation < 0) t->rotation+=4;
        t->lastTimeRotation = 0;
    }
    if(t->lastTimeFall >= minLastTimeFall){
        t->y++;
        if(checkCollision_t(t)){
            t->y--;
            resetT(t);
        }
        t->lastTimeFall = 0;
    }
    minLastTimeFall = 0.3;
    t->currentAction = NO_ACTION;
    t->lastTimeFall+=deltaTime;
    t->lastTimeAction+=deltaTime;
    t->lastTimeRotation+=deltaTime;
}

void render_t(tetromino* t){
    if(t->type == STRAIGHT_T){
        SDL_SetRenderDrawColor(render, 66, 209, 245, 255);
        if(t->rotation == 0 || t->rotation == 2){
            for(int i = 0; i < 4; i++){
                SDL_Rect block = {START_SCREEN+(t->x+i)*TILE_SIZE, (t->y)*TILE_SIZE, TILE_SIZE, TILE_SIZE};
                SDL_RenderFillRect(render, &block);
            }
        }
        else{
            for(int i = 0; i < 4; i++){
                SDL_Rect block = {START_SCREEN+(t->x)*TILE_SIZE, (t->y+i)*TILE_SIZE, TILE_SIZE, TILE_SIZE};
                SDL_RenderFillRect(render, &block);
            }
        }
    }
    if(t->type == SQUARE_T){
        SDL_SetRenderDrawColor(render, 246, 250, 7, 255);
        for(int i = 0; i < 2; i++){
            for(int j = 0; j < 2; j++){
                SDL_Rect block = {START_SCREEN+(t->x+i)*TILE_SIZE, (t->y+j)*TILE_SIZE, TILE_SIZE, TILE_SIZE};
                SDL_RenderFillRect(render, &block);
            }
        }
    }
    if(t->type == TPOL_T){
        SDL_SetRenderDrawColor(render, 250, 7, 238, 255);
        if(t->rotation == 0){
            SDL_Rect block = {0, 0, TILE_SIZE, TILE_SIZE};
            block.x = START_SCREEN+(t->x+1)*TILE_SIZE; block.y = (t->y+1)*TILE_SIZE;
            SDL_RenderFillRect(render, &block);
            block.x = START_SCREEN+(t->x)*TILE_SIZE; block.y = (t->y+1)*TILE_SIZE;
            SDL_RenderFillRect(render, &block);
            block.x = START_SCREEN+(t->x+2)*TILE_SIZE; block.y = (t->y+1)*TILE_SIZE;
            SDL_RenderFillRect(render, &block);
            block.x = START_SCREEN+(t->x+1)*TILE_SIZE; block.y = (t->y)*TILE_SIZE;
            SDL_RenderFillRect(render, &block);
        }
        if(t->rotation == 1){
            SDL_Rect block = {0, 0, TILE_SIZE, TILE_SIZE};
            block.x = START_SCREEN+(t->x+1)*TILE_SIZE; block.y = (t->y+1)*TILE_SIZE;
            SDL_RenderFillRect(render, &block);
            block.x = START_SCREEN+(t->x)*TILE_SIZE; block.y = (t->y+1)*TILE_SIZE;
            SDL_RenderFillRect(render, &block);
            block.x = START_SCREEN+(t->x+1)*TILE_SIZE; block.y = (t->y+2)*TILE_SIZE;
            SDL_RenderFillRect(render, &block);
            block.x = START_SCREEN+(t->x+1)*TILE_SIZE; block.y = (t->y)*TILE_SIZE;
            SDL_RenderFillRect(render, &block);
        }
        if(t->rotation == 2){
            SDL_Rect block = {0, 0, TILE_SIZE, TILE_SIZE};
            block.x = START_SCREEN+(t->x+1)*TILE_SIZE; block.y = (t->y+1)*TILE_SIZE;
            SDL_RenderFillRect(render, &block);
            block.x = START_SCREEN+(t->x)*TILE_SIZE; block.y = (t->y+1)*TILE_SIZE;
            SDL_RenderFillRect(render, &block);
            block.x = START_SCREEN+(t->x+2)*TILE_SIZE; block.y = (t->y+1)*TILE_SIZE;
            SDL_RenderFillRect(render, &block);
            block.x = START_SCREEN+(t->x+1)*TILE_SIZE; block.y = (t->y+2)*TILE_SIZE;
            SDL_RenderFillRect(render, &block);
        }
        if(t->rotation == 3){
            SDL_Rect block = {0, 0, TILE_SIZE, TILE_SIZE};
            block.x = START_SCREEN+(t->x+1)*TILE_SIZE; block.y = (t->y+1)*TILE_SIZE;
            SDL_RenderFillRect(render, &block);
            block.x = START_SCREEN+(t->x+2)*TILE_SIZE; block.y = (t->y+1)*TILE_SIZE;
            SDL_RenderFillRect(render, &block);
            block.x = START_SCREEN+(t->x+1)*TILE_SIZE; block.y = (t->y+2)*TILE_SIZE;
            SDL_RenderFillRect(render, &block);
            block.x = START_SCREEN+(t->x+1)*TILE_SIZE; block.y = (t->y)*TILE_SIZE;
            SDL_RenderFillRect(render, &block);
        }
    }
    if(t->type == LPOL_T){
        SDL_SetRenderDrawColor(render, 240, 155, 36, 255);
        if(t->rotation == 0){
            SDL_Rect block = {START_SCREEN+(t->x)*TILE_SIZE, t->y*TILE_SIZE, TILE_SIZE, TILE_SIZE};
            SDL_RenderFillRect(render, &block);
            block.y+=TILE_SIZE;
            SDL_RenderFillRect(render, &block);
            block.y+=TILE_SIZE;
            SDL_RenderFillRect(render, &block);
            block.x+=TILE_SIZE;
            SDL_RenderFillRect(render, &block);
        }
        if(t->rotation == 1){
            SDL_Rect block = {START_SCREEN+(t->x)*TILE_SIZE, (t->y+1)*TILE_SIZE, TILE_SIZE, TILE_SIZE};
            SDL_RenderFillRect(render, &block);
            block.x+=TILE_SIZE;
            SDL_RenderFillRect(render, &block);
            block.x+=TILE_SIZE;
            SDL_RenderFillRect(render, &block);
            block.y-=TILE_SIZE;
            SDL_RenderFillRect(render, &block);
        }
        if(t->rotation == 2){
            SDL_Rect block = {START_SCREEN+(t->x+1)*TILE_SIZE, t->y*TILE_SIZE, TILE_SIZE, TILE_SIZE};
            SDL_RenderFillRect(render, &block);
            block.y+=TILE_SIZE;
            SDL_RenderFillRect(render, &block);
            block.y+=TILE_SIZE;
            SDL_RenderFillRect(render, &block);
            block.x-=TILE_SIZE;
            block.y-=2*TILE_SIZE;
            SDL_RenderFillRect(render, &block);
        }
        if(t->rotation == 3){
            SDL_Rect block = {START_SCREEN+(t->x)*TILE_SIZE, (t->y+1)*TILE_SIZE, TILE_SIZE, TILE_SIZE};
            SDL_RenderFillRect(render, &block);
            block.x+=TILE_SIZE;
            SDL_RenderFillRect(render, &block);
            block.x+=TILE_SIZE;
            SDL_RenderFillRect(render, &block);
            block.y+=TILE_SIZE;
            block.x-=2*TILE_SIZE;
            SDL_RenderFillRect(render, &block);
        }
    }
    if(t->type == SPOL_T){
        SDL_SetRenderDrawColor(render, 36, 240, 39, 255);
        if(t->rotation == 0 || t->rotation == 2){
            SDL_Rect block = {START_SCREEN+(t->x)*TILE_SIZE, (t->y)*TILE_SIZE, TILE_SIZE, TILE_SIZE};
            SDL_RenderFillRect(render, &block);
            block.y+=TILE_SIZE;
            SDL_RenderFillRect(render, &block);
            block.x+=TILE_SIZE;
            SDL_RenderFillRect(render, &block);
            block.y+=TILE_SIZE;
            SDL_RenderFillRect(render, &block);
        }
        if(t->rotation == 1 || t->rotation == 3){
            SDL_Rect block = {START_SCREEN+(t->x)*TILE_SIZE, (t->y+1)*TILE_SIZE, TILE_SIZE, TILE_SIZE};
            SDL_RenderFillRect(render, &block);
            block.x+=TILE_SIZE;
            SDL_RenderFillRect(render, &block);
            block.y-=TILE_SIZE;
            SDL_RenderFillRect(render, &block);
            block.x+=TILE_SIZE;
            SDL_RenderFillRect(render, &block);
        }
    }
    if(t->type == SPOL2_T){
        SDL_SetRenderDrawColor(render, 245, 42, 42, 255);
        if(t->rotation == 0 || t->rotation == 2){
            SDL_Rect block = {START_SCREEN+(t->x+1)*TILE_SIZE, (t->y)*TILE_SIZE, TILE_SIZE, TILE_SIZE};
            SDL_RenderFillRect(render, &block);
            block.y+=TILE_SIZE;
            SDL_RenderFillRect(render, &block);
            block.x-=TILE_SIZE;
            SDL_RenderFillRect(render, &block);
            block.y+=TILE_SIZE;
            SDL_RenderFillRect(render, &block);
        }
        if(t->rotation == 1 || t->rotation == 3){
            SDL_Rect block = {START_SCREEN+(t->x)*TILE_SIZE, (t->y)*TILE_SIZE, TILE_SIZE, TILE_SIZE};
            SDL_RenderFillRect(render, &block);
            block.x+=TILE_SIZE;
            SDL_RenderFillRect(render, &block);
            block.y+=TILE_SIZE;
            SDL_RenderFillRect(render, &block);
            block.x+=TILE_SIZE;
            SDL_RenderFillRect(render, &block);
        }
    }
    if(t->type == LPOL2_T){
        SDL_SetRenderDrawColor(render, 22, 18, 227, 255);
        if(t->rotation == 0){
            SDL_Rect block = {START_SCREEN+(t->x+1)*TILE_SIZE, (t->y)*TILE_SIZE, TILE_SIZE, TILE_SIZE};
            SDL_RenderFillRect(render, &block);
            block.y+=TILE_SIZE;
            SDL_RenderFillRect(render, &block);
            block.y+=TILE_SIZE;
            SDL_RenderFillRect(render, &block);
            block.x-=TILE_SIZE;
            SDL_RenderFillRect(render, &block);
        }
        if(t->rotation == 1){
            SDL_Rect block = {START_SCREEN+(t->x)*TILE_SIZE, (t->y)*TILE_SIZE, TILE_SIZE, TILE_SIZE};
            SDL_RenderFillRect(render, &block);
            block.x+=TILE_SIZE;
            SDL_RenderFillRect(render, &block);
            block.x+=TILE_SIZE;
            SDL_RenderFillRect(render, &block);
            block.y+=TILE_SIZE;
            SDL_RenderFillRect(render, &block);
        }
        if(t->rotation == 2){
            SDL_Rect block = {START_SCREEN+(t->x)*TILE_SIZE, (t->y)*TILE_SIZE, TILE_SIZE, TILE_SIZE};
            SDL_RenderFillRect(render, &block);
            block.x+=TILE_SIZE;
            SDL_RenderFillRect(render, &block);
            block.x-=TILE_SIZE;
            block.y+=TILE_SIZE;
            SDL_RenderFillRect(render, &block);
            block.y+=TILE_SIZE;
            SDL_RenderFillRect(render, &block);
        }
        if(t->rotation == 3){
            SDL_Rect block = {START_SCREEN+(t->x)*TILE_SIZE, (t->y)*TILE_SIZE, TILE_SIZE, TILE_SIZE};
            SDL_RenderFillRect(render, &block);
            block.y+=TILE_SIZE;
            SDL_RenderFillRect(render, &block);
            block.x+=TILE_SIZE;
            SDL_RenderFillRect(render, &block);
            block.x+=TILE_SIZE;
            SDL_RenderFillRect(render, &block);
        }
    }
}
