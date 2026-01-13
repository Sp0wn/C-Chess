//File guard
#include "../../include/UI/board.h"

//References
#include "../../include/UI/IO.h"

//Include util functions
#include "../../include/UI/ui_utils.h"

//Libraries
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>

const char column_labels[8] = {
    'a',
    'b',
    'c',
    'd',
    'e',
    'f',
    'g',
    'h'
};

void show_board(Board* board, GameConfig* config, GameTheme* theme) {
    WINDOW* board_win;
    int i, row, column;
    int x_offset, y_offset;
    
    //Defines starting points of window
    y_offset = LOGO_HEIGHT + 1;
    x_offset = (getmaxx(stdscr) / 2) - (BOARD_WIDTH / 2);

    //Creates window
    board_win = newwin(BOARD_HEIGHT, BOARD_WIDTH, y_offset, x_offset);
    if(board_win == NULL) {
        endwin();
        fprintf(stderr, "Could not create new window\n");
        exit(EXIT_FAILURE);
    }

    //Adds attributes
    keypad(board_win, TRUE);

    i = 1;
    mvwaddstr(board_win, 0, 4, BOARD_UP);
    if(strncmp(config->side, "W", 2) == 0) {
        for(row = 7; row >= 0; row--) {
            //Prints row number
            mvwprintw(board_win, i, 0, "%i  ", row + 1);
            i++;

            for(column = 0; column < 8; column++) {
                wprintw(board_win, "| %lc ", (*board)[row][column].name);
            }
            waddch(board_win, '|');

            if(row == 0) {
                continue;
            }
            mvwaddstr(board_win, i, 3, BOARD_SPACE);
            i++;
        }
        mvwaddstr(board_win, i, 4, BOARD_DOWN);
        //Prints the labes of the columns
        for(column = 0; column < 8; column++) {
            mvwaddch(board_win, BOARD_HEIGHT - 1, 5 + column * 4, column_labels[column]);
        }

    } else {
        for(row = 0; row < 8; row++) {
            //Prints row number
            mvwprintw(board_win, i, 0, "%i  ", row + 1);
            i++;

            for(column = 7; column >= 0; column--) {
                wprintw(board_win, "| %lc ", (*board)[row][column].name);
            }
            waddch(board_win, '|');

            if(row == 7) {
                continue;
            }
            mvwaddstr(board_win, i, 3, BOARD_SPACE);
            i++;
        }
        mvwaddstr(board_win, i, 4, BOARD_DOWN);
        //Prints the labes of the columns
        for(column = 0; column < 8; column++) {
            mvwaddch(board_win, BOARD_HEIGHT - 1, 5 + column * 4, column_labels[7 - column]);
        }
    }

    wrefresh(board_win);
}
