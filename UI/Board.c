#include "Board.h"

#include "../Game/piece.h"

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

#define UP_BOARD "_______________________________"
#define DOWN_BOARD "‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾"
#define SPACE_BOARD "|---|---|---|---|---|---|---|---|"

void show_board(char* color, piece (*obj)[8][8])
{
    //Function to show the current state of the board
    int x, y;
    getmaxyx(stdscr, y, x);    
    WINDOW* win = newwin(18, 36, 7, (x / 2 - 18));
    keypad(win, TRUE);

    int row, column, line;

    y = 1;

    char column_label[8] = {
        'a',
        'b',
        'c',
        'd',
        'e',
        'f',
        'g',
        'h'
    };

    mvwprintw(win, 0, 4, UP_BOARD);
    if(color[0] == 'W') {
        //Loops for rows
        for(row = 7; row >= 0; row--) {
            //Prints row number
            mvwprintw(win, y, 0, "%i  ", row + 1);
            y++;
            //Prints pieces of each column
            for(column = 0; column < 8; column++) {
                wprintw(win, "| %c ", (*obj)[row][column].name);
            }
            wprintw(win, "|");

            if(row == 0) {
                continue;
            }
            //Prints the spaces between rows
            mvwprintw(win, y, 3, SPACE_BOARD);
            y++;
        }
        mvwprintw(win, y, 4, DOWN_BOARD);
        //Prints the labes of the columns
        for(line = 0; line < 8; line++) {
            mvwprintw(win, 17, 5 + line * 4, "%c", column_label[line]);
        }
    } else {
        for(row = 7; row >= 0; row--) {
            mvwprintw(win, y, 0, "%i  ", 8 - row);
            y++;
            for(column = 0; column < 8; column++) {
                wprintw(win, "| %c ", (*obj)[row][column].name);
            }
            wprintw(win, "|");

            if(row == 0) {
                continue;
            }
            mvwprintw(win, y, 3, SPACE_BOARD);
            y++;
        }
        mvwprintw(win, y, 4, DOWN_BOARD);
        for(line = 0; line < 8; line++) {
            mvwprintw(win, 17, 5 + line * 4, "%c", column_label[7 - line]);
        }
    }

    wrefresh(win);
    delwin(win);
}

void get_move()
{
    keypad(stdscr, TRUE);
    mousemask(BUTTON1_CLICKED, NULL);
    int c = getch();
    MEVENT event;
    switch(c) {
        case KEY_MOUSE:
            if(getmouse(&event) == OK) {
                if(event.bstate & BUTTON1_CLICKED) {
                    printw("X : %i, Y : %i", event.x, event.y);
                    refresh();
                    exit(2);
                }
            }
    }
}
