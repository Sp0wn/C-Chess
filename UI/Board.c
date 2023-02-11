//File guard
#include "Board.h"

//Includes struct reference
#include "../Game/piece.h"

//Libraries
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//Board codes
#define UP_BOARD "_______________________________"
#define DOWN_BOARD "‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾"
#define SPACE_BOARD "|---|---|---|---|---|---|---|---|"

void show_board(char* color, piece (*obj)[8][8], int** moves)
{
    //Function to show the current state of the board
    int x, y;
    getmaxyx(stdscr, y, x);    
    WINDOW* win = newwin(18, 36, 7, (x / 2 - 18));
    keypad(win, TRUE);

    int row, column, line, points, n_moves;
    int* moves_arr;

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

    if(moves != NULL) {
        n_moves = sizeof(moves) / sizeof(*moves[0]);
    } else {
        n_moves = 0;
    }

    mvwprintw(win, 0, 4, UP_BOARD);
    if(color[0] == 'W') {
        //Loops for rows
        for(row = 7; row >= 0; row--) {
            //Prints row number
            mvwprintw(win, y, 0, "%i  ", row + 1);
            y++;
            //Prints pieces of each column
            for(column = 0; column < 8; column++) {
                if(moves != NULL) {
                    for(points = 0; points <= n_moves; points++) {
                        moves_arr = moves[points];
                        if((row == moves_arr[1] && column == moves_arr[0]) && (*obj)[row][column].name == ' ') {
                            wprintw(win, "| ");
                            wattron(win, COLOR_PAIR(3));
                            wprintw(win, "○ ");
                            wattroff(win, COLOR_PAIR(3));
                            break;
                        } else if((row == moves_arr[1] && column == moves_arr[0]) && (*obj)[row][column].name != ' ') {
                            wprintw(win, "| ");
                            wattron(win, COLOR_PAIR(3));
                            wprintw(win, "%c ", (*obj)[row][column].name);
                            wattroff(win, COLOR_PAIR(3));
                            break;
                        } else {
                            if(points == n_moves) {
                                wprintw(win, "| %c ", (*obj)[row][column].name);
                                break;
                            }
                        }
                    }
                } else {
                    wprintw(win, "| %c ", (*obj)[row][column].name);
                }
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
        for(row = 0; row < 8; row++) {
            mvwprintw(win, y, 0, "%i  ", row + 1);
            y++;
            for(column = 7; column >= 0; column--) {
                wprintw(win, "| %c ", (*obj)[row][column].name);
                if(moves != NULL) {
                    for(points = 0; points < n_moves; points++) {
                        moves_arr = moves[points];
                        if(row == moves_arr[1] && column == moves_arr[0] + 1) {
                            wprintw(win, "| ");
                            wattron(win, COLOR_PAIR(3));
                            wprintw(win, "○ ");
                            wattroff(win, COLOR_PAIR(3));
                        }
                    }
                } 
            }
            wprintw(win, "|");

            if(row == 7) {
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

int* get_move(int* old_xy, char* color)
{
    //Function to get the user move input
    int x, y;
    int max_x, min_x;
    int max_y, min_y;

    int row, column;

    int* xy; 

    //Sets pointer for xy array
    xy = malloc(2 * sizeof(int));

    //Deallocates old array
    free(old_xy);

    //Gets board limits 
    getmaxyx(stdscr, y, x);
    min_x = x / 2 - 14;
    max_x = x / 2 + 16;
    min_y = y - (y - 8);
    max_y = y - (y - 22);

    //Enables mouse input
    keypad(stdscr, TRUE);
    mousemask(BUTTON1_CLICKED, NULL);

    //Waits for input
    int ch = getch();
    MEVENT event;
    if(getmouse(&event) == OK && event.bstate &BUTTON1_CLICKED)
    {
        //If not in range of board limits
        //return nothing
        if(event.x > max_x ||
            event.x < min_x ||
            event.y > max_y ||
            event.y < min_y) 
        {
            return NULL;
        } else {
            if(color[0] == 'W') {
                for(row = 0; row < 8; row++) {
                    for(column = 0; column < 8; column++) {
                        //Calculates board square with the
                        //screen coordinates
                        xy[1] = (event.y - min_y) - row;
                        xy[0] = ((event.x - min_x) - 1) / 2 - column;
                        if(xy[1] == row && xy[0] == column) {
                            //Reverses row
                            xy[1] = (xy[1] - 7) * -1;
                            return xy;
                        }
                    }
                }
            } else {
                for(row = 0; row < 8; row++) {
                    for(column = 0; column < 8; column++) {
                        xy[1] = (event.y - min_y) - row;
                        xy[0] = ((event.x - min_x) - 1) / 2 - column;
                        if(xy[1] == row && xy[0] == column) {
                            //Reverses column
                            xy[0] = (xy[0] - 7) * -1;
                            return xy;
                        }
                    }
                }
            }
       }
    }
    return NULL;
}

void make_move(int* move_xy, int* origin_xy, piece (*obj)[8][8], piece blank)
{
    //Gets struct variables
    char symbol = (*obj)[origin_xy[1]][origin_xy[0]].name;
    char color = (*obj)[origin_xy[1]][origin_xy[0]].color;

    //Moves the struct
    (*obj)[move_xy[1]][move_xy[0]].name = symbol;
    (*obj)[move_xy[1]][move_xy[0]].color = color;

    //Resets origin square
    (*obj)[origin_xy[1]][origin_xy[0]] = blank;
    (*obj)[origin_xy[1]][origin_xy[0]].name = ' ';
}
