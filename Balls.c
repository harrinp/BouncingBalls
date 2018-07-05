#include "Balls.h"

Window initWindow(int numBalls, int sleepTime) {
    Window w;

    getmaxyx(stdscr, w.height, w.width);
    w.sleepTime = sleepTime;
    w.numBalls  = numBalls;
    w.balls     = makeBalls(numBalls);
    return w;
}

Ball *makeBalls(int numBalls) {
    Ball *b = malloc(sizeof(*b) * numBalls);

    for (int i = 0; i < numBalls; i++) {
        b[i] = makeBall();
    }
    return b;
}

Ball makeBall() {
    Ball b;

    int  width, height;
    getmaxyx(stdscr, height, width);

    int edge = rand() % 4; // returns 0,1,2,3

    switch (edge) {
    case 0:         // Left edge
        b.x = 1;
        b.y = rand() % height;     // 0 -> height - 1
        break;
    case 1:         // Right edge
        b.x = width - 2;
        b.y = rand() % height;     // 0 -> height - 1
        break;
    case 2:         // Top edge
        b.y = 1;
        b.x = rand() % width;     // 0 -> width - 1
        break;
    case 3:         // Bottom edge
        b.y = height - 2;
        b.x = rand() % width;     // 0 -> height - 1
        break;
    }

    b.avatar = "o";

    b.speedX = ((double)(rand() % 1000))/1000.0;    // Random double 0 -> 1
    b.speedY = 1.0 - b.speedX;
    // All balls have same total magnitude of speed
    b.colorPair = (rand() % 8) + 1; // 1 -> 8
    printf("%d\n", b.colorPair);
    return b;
}

void moveBalls(Window * w) {

    for (int i = 0; i < w->numBalls; i++) {
        /*
        Get the address of the ball I'm working with. This is just for ease of use and makes reading the code simpler
        */
        Ball * ball = &(w->balls[i]);

        ball->y += ball->speedY;
        ball->x += ball->speedX;

        // Check for ball being outside of our window boundaries
        if ((int)(ball)->x >= w->width - 1 || (int)(ball->x) <= 0){
            // change direction
            ball->speedX *= -1;
            ball->x += ball->speedX;
        }
        if ((int)(ball->y) >= w->height - 1 || (int)(ball->y) <= 0){
            // change direction
            ball->speedY *= -1;
            ball->y += ball->speedY;
        }
    }
}

void printWindow(Window * w) {
    for (int i = 0; i < w->numBalls; i++) {
        attron(COLOR_PAIR(w->balls[i].colorPair));      // Applying the ball's color
        mvprintw(w->balls[i].y, w->balls[i].x, w->balls[i].avatar);
        attroff(COLOR_PAIR(w->balls[i].colorPair));     // Stop printing in this color
    }
}

void destroyWindow(Window * w) {
    free(w->balls);
}

/*
    This function abstracts away the color pair process. Basically ncurses deals with colors as color pairs only, foreground and background. Since I only want to color the balls, I used -1 as the background (you MUST call use_default_colors() before doing this). Since I don't care which colors are which, as its random, I'm just using a for loop to make all the possible color pairs with a blank background. When making your own program you may want to use just a single or a couple color pairs. You would make those like this: init_pair(ID, COLOR_RED, COLOR_WHITE); That will have a red letter on a white background. The IDs must start at 1 and go up.

*/
void makeColorPairs(){
    for (int i = 0; i < 8; i++) {
        init_pair(i+1, i, -1);
    }
}
