//File guard
#include "../../include/UI/board.h"

//References
#include "../../include/UI/IO.h"

//Include util functions
#include "../../include/UI/ui_utils.h"

//Libraries
#include <stdbool.h>
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

void show_board(Board* board, GameConfig* config, GameTheme* theme, Moves* moves) {
    int* move_xy;
    WINDOW* board_win;
    int x_offset, y_offset;
    int i, row, column, point;
    
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
                if(moves != NULL) {
                    //Loops through possible moves
                    for(point = 0; point < moves->size; point++) {
                        move_xy = moves->list[point];

                        //Checks if array equals current square
                        if(!(row == move_xy[1] && column == move_xy[0])) {
                            //Prints default color
                            if(point == (moves->size - 1)) {
                                wprintw(board_win, "| %lc ", show_piece(board, row, column, config->style));
                            }
                            continue;
                        }

                        //Prints possible moves
                        if((*board)[row][column].name == ' ') {
                            wprintw(board_win, "| ");
                            turn_on_color(board_win, theme->color_black);
                            wprintw(board_win, "○ ");
                            turn_off_color(board_win, theme->color_black);
                            break;

                        //Highlights capturable pieces
                        } else if((*board)[row][column].name != ' ') {
                            wprintw(board_win, "| ");
                            turn_on_color(board_win, theme->color_black);
                            wprintw(board_win, "%lc ", show_piece(board, row, column, config->style));
                            turn_off_color(board_win, theme->color_black);
                            break;
                        }
                    }

                } else {
                    wprintw(board_win, "| %lc ", show_piece(board, row, column, config->style));
                }
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
                if(moves != NULL) {
                    //Loops through possible moves
                    for(point = 0; point < moves->size; point++) {
                        move_xy = moves->list[point];

                        //Checks if array equals current square
                        if(!(row == move_xy[1] && column == move_xy[0])) {
                            //Prints default color
                            if(point == (moves->size - 1)) {
                                wprintw(board_win, "| %lc ", show_piece(board, row, column, config->style));
                            }
                            continue;
                        }

                        //Prints possible moves
                        if((*board)[row][column].name == ' ') {
                            wprintw(board_win, "| ");
                            turn_on_color(board_win, theme->color_black);
                            wprintw(board_win, "○ ");
                            turn_off_color(board_win, theme->color_black);
                            break;

                        //Highlights capturable pieces
                        } else if((*board)[row][column].name != ' ') {
                            wprintw(board_win, "| ");
                            turn_on_color(board_win, theme->color_black);
                            wprintw(board_win, "%lc ", show_piece(board, row, column, config->style));
                            turn_off_color(board_win, theme->color_black);
                            break;
                        }
                    }

                } else {
                    wprintw(board_win, "| %lc ", show_piece(board, row, column, config->style));
                }
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

int show_piece(Board* board, int row, int column, char* style) {
    int piece, color;

    piece = (*board)[row][column].name;
    color = (*board)[row][column].color;

    if(strncmp(style, "UNICODE", 8) == 0) {
        if(piece == 'p' || piece == 'P') {
            piece = (color == 'w') ? 0x2659 : 0x265F; 
        } else if(piece == 'n' || piece == 'N') {
            piece = (color == 'w') ? 0x2658 : 0x265E;
        } else if(piece == 'b' || piece == 'B') {
            piece = (color == 'w') ? 0x2657 : 0x265D;
        } else if(piece == 'r' || piece == 'R') {
            piece = (color == 'w') ? 0x2656 : 0x265C;
        } else if(piece == 'q' || piece == 'Q') {
            piece = (color == 'w') ? 0x2655 : 0x265B;
        } else if(piece == 'k' || piece == 'K') {
            piece = (color == 'w') ? 0x2654 : 0x265A;
        } else if(piece == ' ' || piece == ' ') {
            piece = 32;
        }
    }

    return piece;
}

int* get_move(int* old_xy, char* side) {
    MEVENT event;
    int row, column, ch;
    int max_x, min_x, max_y, min_y;

    //Deallocates old coordinates
    free(old_xy);

    //Allocates memory for the coordinates
    int* xy = malloc(2 * sizeof(int));
    if(xy == NULL) {
        if(stdscr != NULL) {
            endwin();
        }
        perror("Could not allocate memory");
        exit(EXIT_FAILURE);
    }

    //Gets board limits
    min_x = (getmaxx(stdscr) / 2) - ((BOARD_WIDTH / 2) - 4);
    max_x = (getmaxx(stdscr) / 2) + ((BOARD_WIDTH / 2) - 2);
    min_y = LOGO_HEIGHT + 2;
    max_y = min_y + BOARD_HEIGHT - 4;

    //Enables mouse input
    keypad(stdscr, TRUE);
    mousemask(BUTTON1_CLICKED, NULL);

    //Waits for input
    ch = getch();
    if(getmouse(&event) == OK && event.bstate &BUTTON1_CLICKED) {
        //Checks if in range of board limits
        if(event.x > max_x || event.x < min_x || 
                event.y > max_y || event.y < min_y) {
            return NULL;
        }

        if(strncmp(side, "W", 2) == 0) {
            for(row = 0; row < 8; row++) {
                for(column = 0; column < 8; column++) {
                    //Translates screen coordinates to board coordinates
                    xy[1] = (event.y - min_y) - row;
                    xy[0] = ((event.x - min_x) - 1) / 2 - column;

                    if(xy[1] == row && xy[0] == column) {
                        //Reverses column
                        xy[1] = (xy[1] - 7) * -1;
                        return xy;
                    }
                }
            }

        }  else {
            for(row = 0; row < 8; row++) {
                for(column = 0; column < 8; column++) {
                    xy[1] = (event.y - min_y) - row;
                    xy[0] = ((event.x - min_x) - 1) / 2 - column;

                    if(xy[1] == row && xy[0] == column) {
                        //Reverses row
                        xy[0] = (xy[0] - 7) * -1;
                        return xy;
                    }
                }
            }
        }
    }

    return NULL;
}

bool make_move(Board* board, int* origin_xy, int* target_xy, Moves* moves) {
    int* move_xy;
    int moves_size;
    char origin_piece, origin_color;

    origin_piece = (*board)[origin_xy[1]][origin_xy[0]].name;
    origin_color = (*board)[origin_xy[1]][origin_xy[0]].color;

    //Checks if struct is not empty
    if(moves == NULL) {
        return false;
    }

    //Assigns number of moves to local variable
    if(moves->size > 0) {
        moves_size = moves->size;
    } else {
        return false;
    }

    //Checks if target move is not empty
    if(target_xy == NULL) {
        return false;
    }

    while(moves_size > 0) {
        move_xy = moves->list[moves_size - 1];
        if((target_xy[0] == move_xy[0]) && (target_xy[1] == move_xy[1])) {
            (*board)[target_xy[1]][target_xy[0]].name = origin_piece;
            (*board)[target_xy[1]][target_xy[0]].color = origin_color;
            (*board)[origin_xy[1]][origin_xy[0]].name = ' ';
            (*board)[origin_xy[1]][origin_xy[0]].color = '\0';
            return true;
        }
        moves_size--;
    }

    return false;
}
