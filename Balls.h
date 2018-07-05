#ifndef BALLS_H
#define BALLS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>
#include <math.h>

typedef struct _Ball{
    // Position
    double x;
    double y;
    // How we display the ball
    char * avatar;
    // Speed (What we add to the x and y each loop iteration)
    double speedX;
    double speedY;

    int colorPair;
} Ball;

typedef struct _Window {
    int height;
    int width;
    int sleepTime;
    int numBalls;
    Ball * balls;
} Window;

Window initWindow(int,int);
Ball * makeBalls();
Ball makeBall();
void moveBalls(Window *);
void printWindow(Window *);
void destroyWindow(Window *);
void makeColorPairs();

#endif
