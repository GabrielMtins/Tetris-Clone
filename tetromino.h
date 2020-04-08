#ifndef TETROMINO_H
#define TETROMINO_H

typedef struct{
    int x, y;
    int type;
    int rotation;
    int currentAction;
    double lastTimeFall;
    double lastTimeAction;
    double lastTimeRotation;
} tetromino;

void input_t(tetromino* t);

int checkCollision_t(tetromino* t);

void resetT(tetromino* t);

void updateLogic_t(tetromino* t);

void render_t(tetromino* t);

#endif
