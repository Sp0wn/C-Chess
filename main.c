//Interface functions
#include "UI/IO.h"
#include "UI/Board.h"

//Game functions
#include "Game/set.h"
#include "Game/rules.h"

//Structs
#include "Game/piece.h"
#include "Game/clock.h"

//Standard libraries
#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <unistd.h>
#include <pthread.h>

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

int main()
{
    //Declares board array and it's pointer
    piece board[8][8], (*b_ptr)[8][8];
    const piece reset_p;
    b_ptr = &board;

    //Declares variables
    int option, run;

    //Loads user config
    char** config;
    config = load_config();

    int* theme;
    theme = load_theme(config[1]);

    //Sets locale
    char* locale;
    locale = setlocale(LC_ALL, "");

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

    run = 1;

    show_logo(theme, 1);

    //Main program loop
    while(run) {
        option = main_menu(config[0], theme);
        switch(option) {
            //Exit
            case 0:
                run = 0;
                endwin();
                exit(0);

            case 1:
                break;

            case 2:
                break;

            case 3:
                break;

            case 4:
                show_logo(theme, 0);

                //Sets struct for clock
                M_clock Clock_struct;
                Clock_struct.turn = 1;
                Clock_struct.end = 0;

                //Sets king attributes
                int* w_castle;
                w_castle = malloc(2 * sizeof(int));
                int* b_castle;
                b_castle = malloc(2 * sizeof(int));
                int* w_king;
                w_king = malloc(2 * sizeof(int));
                w_king[0] = 4;
                w_king[1] = 0;
                int* b_king;
                b_king = malloc(2 * sizeof(int));
                b_king[0] = 4;
                b_king[1] = 7;
                int** attack_w; 
                int** attack_b; 

                //Initial screens
                set_time(&Clock_struct, theme);
                set_pieces(b_ptr);
                show_board(config[2], b_ptr, NULL, NULL, theme, NULL, ' ', config[3]);

                //Creates thread
                pthread_t Clock_P;
                pthread_create(&Clock_P, NULL, load_clock, &Clock_struct);

                //Sets vars for moves and different game values
                int *move_1w, *move_2w, *move_1b, *move_2b;
                int **moves_w, **moves_b;
                int wm_done, bm_done;
                int row, column;
                int xy_temp[2];

                move_1w = move_2w = move_1b = move_2b = NULL;
                moves_w = moves_b = attack_w = attack_b = NULL;

                while(1) {
                    //Checks if check or mate
                    attack_w = square_attacked(w_king, 'w', NULL, b_ptr);
                    moves_w = NULL;
                    for(row = 0;row < 8; row++) {
                        for(column = 0; column < 8; column++) {
                            xy_temp[0] = column;
                            xy_temp[1] = row;
                            if((*b_ptr)[row][column].color == 'w' && (*b_ptr)[row][column].name == 'K') {
                                moves_w = legal_moves(w_king, b_ptr, 'w', attack_w, w_castle, w_king, NULL);
                            } else if((*b_ptr)[row][column].color == 'w') {
                                moves_w = legal_moves(xy_temp, b_ptr, 'w', attack_w, w_castle, w_king, NULL);
                            } else {
                                continue;
                            }
                            if((moves_w != NULL)) {
                                break;
                            }
                        }
                        if((moves_w != NULL)) {
                            break;
                        }
                    }
                    if((attack_w != NULL) && moves_w == NULL) {
                        pthread_cancel(Clock_P);
                        show_board(config[2], b_ptr, NULL, NULL, theme, NULL, 'b', config[3]);
                        sleep(5);
                        endwin();
                        exit(0);
                    } else if((attack_w != NULL)) {
                        show_board(config[2], b_ptr, NULL, NULL, theme, w_king, ' ', config[3]);
                    }

                    //Gets piece to move
                    if (Clock_struct.end == 1) break;
                    do {
                        move_1w = get_move(move_1w, config[2]);
                        attack_w = square_attacked(w_king, 'w', NULL, b_ptr);
                        moves_w = legal_moves(move_1w, b_ptr, 'w', attack_w, w_castle, w_king, NULL);
                    } while(move_1w == NULL || moves_w == NULL);
                    if (Clock_struct.end == 1) break;

                    if((attack_w != NULL)) {
                        show_board(config[2], b_ptr, moves_w, NULL, theme, w_king, ' ', config[3]);
                    } else {
                        show_board(config[2], b_ptr, moves_w, NULL, theme, NULL, ' ', config[3]);
                    }

                    //Gets square to move the piece
                    if (Clock_struct.end == 1) break;
                    do {
                        move_2w = get_move(move_2w, config[2]);
                        wm_done = make_move(move_2w, move_1w, moves_w, b_ptr, reset_p, w_castle, w_king);
                    } while(move_2w == NULL || wm_done == 0);
                    if (Clock_struct.end == 1) break;

                    show_board(config[2], b_ptr, NULL, move_2w, theme, NULL, ' ', config[3]);

                    //Changes turn to black
                    Clock_struct.turn = 2;

                    attack_b = square_attacked(b_king, 'b', NULL, b_ptr);
                    moves_b = NULL;
                    for(row = 0;row < 8; row++) {
                        for(column = 0; column < 8; column++) {
                            xy_temp[0] = column;
                            xy_temp[1] = row;
                            if((*b_ptr)[row][column].color == 'b' && (*b_ptr)[row][column].color == 'k') {
                                moves_b = legal_moves(b_king, b_ptr, 'b', attack_b, b_castle, b_king, NULL);
                            } else if((*b_ptr)[row][column].color == 'b') {
                                moves_b = legal_moves(xy_temp, b_ptr, 'b', attack_b, b_castle, b_king, NULL);
                            } else {
                                continue;
                            }
                            if((moves_b != NULL)) {
                                break;
                            }
                        }
                        if((moves_b != NULL)) {
                            break;
                        }
                    }
                    if((attack_b != NULL) && moves_b == NULL) {
                        pthread_cancel(Clock_P);
                        show_board(config[2], b_ptr, NULL, NULL, theme, NULL, 'w', config[3]);
                        sleep(5);
                        endwin();
                        exit(0);
                    } else if((attack_b != NULL)) {
                        show_board(config[2], b_ptr, NULL, NULL, theme, b_king, ' ', config[3]);
                    }
                    if (Clock_struct.end == 1) break;
                    do {
                        move_1b = get_move(move_1b, config[2]);
                        attack_b = square_attacked(b_king, 'b', NULL, b_ptr);
                        moves_b = legal_moves(move_1b, b_ptr, 'b', attack_b, b_castle, b_king, NULL);
                    } while(move_1b == NULL || moves_b == NULL);
                    if (Clock_struct.end == 1) break;

                    if((attack_b != NULL)) {
                        show_board(config[2], b_ptr, moves_b, NULL, theme, b_king, ' ', config[3]);
                    } else {
                        show_board(config[2], b_ptr, moves_b, NULL, theme, NULL, ' ', config[3]);
                    }

                    if (Clock_struct.end == 1) break;
                    do {
                        move_2b = get_move(move_2b, config[2]);
                        bm_done = make_move(move_2b, move_1b, moves_b, b_ptr, reset_p, b_castle, b_king);
                    } while(move_2b == NULL || bm_done == 0);
                    if (Clock_struct.end == 1) break;

                    show_board(config[2], b_ptr, NULL, move_2b, theme, NULL, ' ', config[3]);
                    //Changes turn to white
                    Clock_struct.turn = 1;
                }
                break;

            //Options
            case 5:
                options_menu(config[0], config[1], config[2], theme, config[3]);
                clear_config_cache(config, theme);
                config = load_config();
                theme = load_theme(config[1]);
                break;
        }
        show_logo(theme, 0);
    }

    endwin();
    clear_config_cache(config, theme);

    return 0;
}
