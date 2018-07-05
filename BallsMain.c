#include "Balls.h"

int main(int argc, char *argv[]) {
    int numBalls = 100;
    if (argc > 1){
        numBalls = atoi(argv[1]);
    }
    srand(time(NULL));
    initscr();              // Start ncurses
    nodelay(stdscr, TRUE);  // Don't wait for \n for getch to parse input
    cbreak();               // Switch off input buffering
    curs_set(FALSE);        // Don't place a cursor on the screen
    start_color();
    use_default_colors();

    makeColorPairs();

    Window w = initWindow(numBalls, 50000);
    
    while (getch() == ERR) {
        clear();
        moveBalls(&w);
        printWindow(&w);
        usleep(w.sleepTime);
    }
    destroyWindow(&w);
    nodelay(stdscr, FALSE);
    nocbreak();
    endwin();
    return 0;
}
