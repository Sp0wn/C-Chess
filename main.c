//User interface functions
#include "include/UI/IO.h"

//Standard ibraries
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>

//Main UI library
#include <ncurses.h>

//Color codes
#define BLUE 4
#define GREEN 2
#define RED 1

#define PURPLE 5
#define YELLOW 11
#define ORANGE 208

#define WHITE 15
#define GREY 7
#define BLACK 16

int main(int argc, char* argv[])
{
    //Starts main window
    initscr();
    raw();
    noecho();
    start_color();
    use_default_colors();
    curs_set(FALSE);

    //Inits color pairs
    init_pair(1, BLUE, -1);
    init_pair(2, GREEN, -1);
    init_pair(3, RED, -1);
    init_pair(4, PURPLE, -1);
    init_pair(5, YELLOW, -1);
    init_pair(6, ORANGE, -1);
    init_pair(7, WHITE, -1);
    init_pair(8, GREY, -1);
    init_pair(9, BLACK, -1);

    int theme[] = {2};
    bool animation = true;

    show_logo(theme, animation);

    endwin();
    return 0;
}
