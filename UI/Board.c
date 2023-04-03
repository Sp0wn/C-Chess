//File guard
#include "Board.h"

//Includes struct reference
#include "../Game/piece.h"

//Includes set functions
#include "../Game/set.h"

//Libraries
#include <curses.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wchar.h>

//Board codes
#define UP_BOARD "_______________________________"
#define DOWN_BOARD "‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾"
#define SPACE_BOARD "|---|---|---|---|---|---|---|---|"

void show_board(char* color, piece (*obj)[8][8], int** moves, int* last_move, int* theme, int* king, char c_win, char* style)
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
        n_moves = (*(moves-1))[0];
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
                    for(points = 1; points <= n_moves; points++) {
                        moves_arr = moves[points - 1];
                        //Prints point highlighted if a move is possible and the square
                        //is empty
                        if((row == moves_arr[1] && column == moves_arr[0]) && (*obj)[row][column].name == ' ') {
                            wprintw(win, "| ");
                            wattron(win, COLOR_PAIR(theme[2]));
                            wprintw(win, "○ ");
                            wattroff(win, COLOR_PAIR(theme[2]));
                            break;
                        //Prints the piece highlighted if a move is possible and the 
                        //square is used by another piece
                        } else if((row == moves_arr[1] && column == moves_arr[0]) && (*obj)[row][column].name != ' ') {
                            wprintw(win, "| ");
                            wattron(win, COLOR_PAIR(theme[2]));
                            wprintw(win, "%lc ", show_piece(row, column, style, obj));
                            wattroff(win, COLOR_PAIR(theme[2]));
                            break;
                        } else {
                            if(points == n_moves) {
                                if(king != NULL) {
                                    if(king[0] == column && king[1] == row) {
                                        wprintw(win, "| ");
                                        wattron(win, COLOR_PAIR(theme[1]));
                                        wprintw(win, "%lc ", show_piece(row, column, style, obj));
                                        wattroff(win, COLOR_PAIR(theme[1]));
                                        continue;
                                    }
                                }
                                wprintw(win, "| %lc ", show_piece(row, column, style, obj));
                            }
                        }
                    }
                } else if(last_move != NULL) {
                    if(row == last_move[1] && column == last_move[0]) {
                        wprintw(win, "| ");
                        wattron(win, COLOR_PAIR(theme[0]));
                        wprintw(win, "%lc ", show_piece(row, column, style, obj));
                        wattroff(win, COLOR_PAIR(theme[0]));
                    } else {
                        if(king != NULL) {
                            if(king[0] == column && king[1] == row) {
                                wprintw(win, "| ");
                                wattron(win, COLOR_PAIR(theme[1]));
                                wprintw(win, "%lc ", show_piece(row, column, style, obj));
                                wattroff(win, COLOR_PAIR(theme[1]));
                                continue;
                            }
                        } 
                        wprintw(win, "| %lc ", show_piece(row, column, style, obj));
                    }
                } else {
                    wprintw(win, "| %lc ", show_piece(row, column, style, obj));
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
                if(moves != NULL) {
                    for(points = 1; points <= n_moves; points++) {
                        moves_arr = moves[points - 1];
                        if((row == moves_arr[1] && column == moves_arr[0]) && (*obj)[row][column].name == ' ') {
                            wprintw(win, "| ");
                            wattron(win, COLOR_PAIR(theme[2]));
                            wprintw(win, "○ ");
                            wattroff(win, COLOR_PAIR(theme[2]));
                            break;
                        } else if((row == moves_arr[1] && column == moves_arr[0]) && (*obj)[row][column].name != ' ') {
                            wprintw(win, "| ");
                            wattron(win, COLOR_PAIR(theme[2]));
                            wprintw(win, "%lc ", show_piece(row, column, style, obj));
                            wattroff(win, COLOR_PAIR(theme[2]));
                            break;
                        } else {
                            if(points == n_moves) {
                                if(king != NULL) {
                                    if(king[0] == column && king[1] == row) {
                                        wprintw(win, "| ");
                                        wattron(win, COLOR_PAIR(theme[1]));
                                        wprintw(win, "%lc ", show_piece(row, column, style, obj));
                                        wattroff(win, COLOR_PAIR(theme[1]));
                                        continue;
                                    }
                                }
                                wprintw(win, "| %lc ", show_piece(row, column, style, obj));
                            }
                        }
                    }
                } else if(last_move != NULL) {
                    if(row == last_move[1] && column == last_move[0]) {
                        wprintw(win, "| ");
                        wattron(win, COLOR_PAIR(theme[0]));
                        wprintw(win, "%lc ", show_piece(row, column, style, obj));
                        wattroff(win, COLOR_PAIR(theme[0]));
                    } else {
                        if(king != NULL) {
                            if(king[0] == column && king[1] == row) {
                                wprintw(win, "| ");
                                wattron(win, COLOR_PAIR(theme[1]));
                                wprintw(win, "%lc ", show_piece(row, column, style, obj));
                                wattroff(win, COLOR_PAIR(theme[1]));
                                continue;
                            }
                        } 
                        wprintw(win, "| %lc ", show_piece(row, column, style, obj));
                    }
                } else {
                    wprintw(win, "| %lc ", show_piece(row, column, style, obj));
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

int show_promotion(int *theme, piece (*obj)[8][8], char p_color, int column)
{
    int x, y;
    char knight_symbol, bishop_symbol, rook_symbol, queen_symbol;
    getmaxyx(stdscr, y, x);   

    knight_symbol = (p_color == 'w') ? 'N' : 'n';
    bishop_symbol = (p_color == 'w') ? 'B' : 'b';
    rook_symbol = (p_color == 'w') ? 'R' : 'r';
    queen_symbol = (p_color == 'w') ? 'Q' : 'q';

    if(p_color == 'w') {
        WINDOW* win = newwin(7, 3, 8, (x / 2 - 18) + 4 + (column * 4));
        keypad(win, TRUE);
        mousemask(BUTTON1_CLICKED, NULL);
        wattron(win, COLOR_PAIR(theme[1]));

        mvwprintw(win, 0, 0, " %c", queen_symbol);
        mvwprintw(win, 2, 0, " %c", rook_symbol);
        mvwprintw(win, 4, 0, " %c", bishop_symbol);
        mvwprintw(win, 6, 0, " %c", knight_symbol);
        wrefresh(win);

        int ch = wgetch(win);
        MEVENT event;
        if(getmouse(&event) == OK && event.bstate &BUTTON1_CLICKED) {
            int option = (event.y / 2) - 3;
            return option;
        }
        delwin(win);
    } else {
        WINDOW* win = newwin(7, 3, 16, (x / 2 - 18) + 4 + (column * 4));
        keypad(win, TRUE);
        mousemask(BUTTON1_CLICKED, NULL);
        wattron(win, COLOR_PAIR(theme[1]));

        mvwprintw(win, 0, 0, " %c", knight_symbol);
        mvwprintw(win, 2, 0, " %c", bishop_symbol);
        mvwprintw(win, 4, 0, " %c", rook_symbol);
        mvwprintw(win, 6, 0, " %c", queen_symbol);
        wrefresh(win);

        int ch = wgetch(win);
        MEVENT event;
        if(getmouse(&event) == OK && event.bstate &BUTTON1_CLICKED) {
            int option = abs((event.y / 2) - 11) + 1;
            return option;
        }
        delwin(win);
    }
    return 0;
}

int show_piece(int row, int column, char *style, piece (*obj)[8][8])
{
    int style_val, piece;
    char symbol, color;

    if(strcmp(style, "ASCII  ") == 0) {
        style_val = 1;
    } else {
        style_val = 2;
    }

    symbol = (*obj)[row][column].name;
    color = (*obj)[row][column].color;
    
    if(style_val == 1) {
        if(symbol == 'p' || symbol == 'P') {
            piece = (color == 'w') ? 80 : 112; 
        } else if(symbol == 'n' || symbol == 'N') {
            piece = (color == 'w') ? 78 : 110;
        } else if(symbol == 'b' || symbol == 'B') {
            piece = (color == 'w') ? 66 : 98;
        } else if(symbol == 'r' || symbol == 'R') {
            piece = (color == 'w') ? 82 : 114;
        } else if(symbol == 'q' || symbol == 'Q') {
            piece = (color == 'w') ? 81 : 113;
        } else if(symbol == 'k' || symbol == 'K') {
            piece = (color == 'w') ? 75 : 107;
        } else if(symbol == ' ' || symbol == ' ') {
            piece = 32;
        }
    } else {
        if(symbol == 'p' || symbol == 'P') {
            piece = (color == 'w') ? 0x2659 : 0x265F; 
        } else if(symbol == 'n' || symbol == 'N') {
            piece = (color == 'w') ? 0x2658 : 0x265E;
        } else if(symbol == 'b' || symbol == 'B') {
            piece = (color == 'w') ? 0x2657 : 0x265D;
        } else if(symbol == 'r' || symbol == 'R') {
            piece = (color == 'w') ? 0x2656 : 0x265C;
        } else if(symbol == 'q' || symbol == 'Q') {
            piece = (color == 'w') ? 0x2655 : 0x265B;
        } else if(symbol == 'k' || symbol == 'K') {
            piece = (color == 'w') ? 0x2654 : 0x265A;
        } else if(symbol == ' ' || symbol == ' ') {
            piece = 32;
        }
    }
    return piece;
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

int make_move(int* move_xy, int* origin_xy, int** legal_moves, piece (*obj)[8][8], piece blank, int* castle)
{
    int n_moves;
    int* legal_array;
    char rook_symbol;

    //Gets array size
    if (legal_moves != NULL) {
        n_moves = (*(legal_moves-1))[0];
    } else {
        n_moves = 0;
    }

    //Gets struct variables
    char symbol = (*obj)[origin_xy[1]][origin_xy[0]].name;
    char color = (*obj)[origin_xy[1]][origin_xy[0]].color;

    rook_symbol = (color == 'w') ? 'R' : 'r';

    while(n_moves > 0) {
        legal_array = legal_moves[n_moves - 1];
        if((move_xy[0] == legal_array[0]) && (move_xy[1] == legal_array[1])) {
            //Resets square of en passant
            if((symbol == 'P' || symbol == 'p') && (*obj)[move_xy[1]][move_xy[0]].name == ' ') {
                if(color == 'w') {
                    (*obj)[move_xy[1] - 1][move_xy[0]] = blank;
                    (*obj)[move_xy[1] - 1][move_xy[0]].name = ' ';
                } else {
                    (*obj)[move_xy[1] + 1][move_xy[0]] = blank;
                    (*obj)[move_xy[1] + 1][move_xy[0]].name = ' ';
                }
            }
            //Sets castle privilege
            if(symbol == 'K' || symbol == 'k') {
                castle[0] = 0;
                castle[1] = 0;
                //Short castle
                if(move_xy[0] - origin_xy[0] == 2) {
                    //Resets rook square and moves rook
                    (*obj)[move_xy[1]][7] = blank;
                    (*obj)[move_xy[1]][7].name = ' ';
                    (*obj)[move_xy[1]][5].name = rook_symbol;
                    (*obj)[move_xy[1]][5].color = color;
                //Long castle
                } else if(move_xy[0] - origin_xy[0] == -2) {
                    (*obj)[move_xy[1]][0] = blank;
                    (*obj)[move_xy[1]][0].name = ' ';
                    (*obj)[move_xy[1]][3].name = rook_symbol;
                    (*obj)[move_xy[1]][3].color = color;
                }
            }
            if(symbol == 'R' || symbol == 'r') {
                if(origin_xy[0] == 0) {
                    castle[0] = 0;
                } else if(origin_xy[0] == 7) {
                    castle[1] = 0;
                }
            }
            //Resets en passant attribute
            set_enpassant(obj);
            //Sets en passant attribute
            if((symbol == 'P' || symbol == 'p') && abs(move_xy[1] - origin_xy[1]) == 2) {
                (*obj)[move_xy[1]][move_xy[0]].enpassant = 1;
            }
            //Moves the struct
            (*obj)[move_xy[1]][move_xy[0]].name = symbol;
            (*obj)[move_xy[1]][move_xy[0]].color = color;
            //Resets origin square
            (*obj)[origin_xy[1]][origin_xy[0]] = blank;
            (*obj)[origin_xy[1]][origin_xy[0]].name = ' ';
            return 1;
        } 
        n_moves--; 
    }
    return 0;
}

int make_promotion(int option, int *origin_xy, piece (*obj)[8][8], char p_color)
{
    char knight_symbol, bishop_symbol, rook_symbol, queen_symbol;
    knight_symbol = (p_color == 'w') ? 'N' : 'n';
    bishop_symbol = (p_color == 'w') ? 'B' : 'b';
    rook_symbol = (p_color == 'w') ? 'R' : 'r';
    queen_symbol = (p_color == 'w') ? 'Q' : 'q';

    switch(option) {
        case 1:
            (*obj)[origin_xy[1]][origin_xy[0]].name = queen_symbol;
            break;
        case 2:
            (*obj)[origin_xy[1]][origin_xy[0]].name = rook_symbol;
            break;
        case 3:
            (*obj)[origin_xy[1]][origin_xy[0]].name = bishop_symbol;
            break;
        case 4:
            (*obj)[origin_xy[1]][origin_xy[0]].name = knight_symbol;
            break;
        default:
            return 0;
    }
    return 1;
}

