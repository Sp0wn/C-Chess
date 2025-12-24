#include <ncurses.h>

int main(void) {
    //Starts main window
    initscr();
    raw();
    noecho();
    start_color();
    use_default_colors();
    curs_set(FALSE);

    endwin();
    return 0;
} 
