//Header file
#include "../../include/UI/IO.h"

//Libraries
#include <ncurses.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>

void show_logo(int* theme, bool animation) {
    int8_t i;
    int16_t max_x, x;

    //Buffers each line in multiple arrays
    char* line1 = "  _____             _____ _";
    char* line2 = " / ____|           / ____| |                      __";
    char* line3 = "| |       ______  | |    | |__   ___  ___ ___    (  )";
    char* line4 = "| |      |______| | |    | '_ \\ / _ \\/ __/ __|    ||";
    char* line5 = "| |____           | |____| | | |  __/\\__ \\__ \\   /__\\";
    char* line6 = " \\_____|           \\_____|_| |_|\\___||___/___/  (____)";

    //Stores the logo lines in a single array of pointers
    char* lines[6] = {line1, line2, line3, line4, line5, line6};

    //Gets the center of the x axis
    //and subtracts the offset (half of the logo length)
    max_x = getmaxx(stdscr);
    x = max_x / 2 - 27;

    clear();

    attron(COLOR_PAIR(theme[0]));

    //Prints the logo
    for(i = 0; i < 6; i++) {
        mvprintw(i, x, "%s", lines[i]);
        //Adds delays of 2.5s for a smooth display
        if(animation == true) {
            refresh();
            usleep(250000);
        }
    }

    attroff(COLOR_PAIR(theme[0]));

    refresh();
}
