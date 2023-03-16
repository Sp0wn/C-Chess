//Interface functions
#include "UI/IO.h"
#include "UI/Board.h"

//Game functions
#include "Game/set.h"
#include "Game/rules.h"

#include "Game/piece.h"

//Standard libraries
#include <curses.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <locale.h>

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
                set_pieces(b_ptr);
                show_board(config[2], b_ptr, NULL, NULL, theme);

                int* w_castle;
                w_castle = malloc(2 * sizeof(int));
                int* b_castle;
                b_castle = malloc(2 * sizeof(int));

                int* c = get_move(NULL, config[2]);
                int **b1 = legal_moves(c, b_ptr, (*b_ptr)[c[1]][c[0]].color, NULL, w_castle);
                show_board(config[2], b_ptr, b1, NULL, theme);
                int* d = get_move(NULL, config[2]);
                make_move(d, c, b1, b_ptr, reset_p, w_castle);
                show_board(config[2], b_ptr, NULL, NULL, theme);

                int* c2 = get_move(NULL, config[2]);
                int **b2 = legal_moves(c2, b_ptr, (*b_ptr)[c2[1]][c2[0]].color, d, b_castle);
                show_board(config[2], b_ptr, b2, NULL, theme);
                int* d2 = get_move(NULL, config[2]);
                make_move(d2, c2, b2, b_ptr, reset_p, b_castle);
                show_board(config[2], b_ptr, NULL, NULL, theme);

                int* c3 = get_move(NULL, config[2]);
                int **b3 = legal_moves(c3, b_ptr, (*b_ptr)[c3[1]][c3[0]].color, d2, w_castle);
                show_board(config[2], b_ptr, b3, NULL, theme);
                int* d3 = get_move(NULL, config[2]);
                make_move(d3, c3, b3, b_ptr, reset_p, w_castle);
                show_board(config[2], b_ptr, NULL, NULL, theme);

                int* c4 = get_move(NULL, config[2]);
                int **b4 = legal_moves(c4, b_ptr, (*b_ptr)[c4[1]][c4[0]].color, d3, b_castle);
                show_board(config[2], b_ptr, b4, NULL, theme);
                int* d4 = get_move(NULL, config[2]);
                make_move(d4, c4, b4, b_ptr, reset_p, b_castle);
                show_board(config[2], b_ptr, NULL, NULL, theme);

                int* a = get_move(NULL, config[2]);
                int **b = legal_moves(a, b_ptr, (*b_ptr)[a[1]][a[0]].color, d4, w_castle);
                show_board(config[2], b_ptr, b, NULL, theme);
                int* d5 = get_move(NULL, config[2]);
                make_move(d5, a, b, b_ptr, reset_p, w_castle);
                show_board(config[2], b_ptr, NULL, NULL, theme);

                int* c5 = get_move(NULL, config[2]);
                int **b5 = legal_moves(c5, b_ptr, (*b_ptr)[c5[1]][c5[0]].color, d5, b_castle);
                show_board(config[2], b_ptr, b5, NULL, theme);
                int* d6 = get_move(NULL, config[2]);
                make_move(d6, c5, b5, b_ptr, reset_p, b_castle);
                show_board(config[2], b_ptr, NULL, NULL, theme);

                int* c6 = get_move(NULL, config[2]);
                int **b6 = legal_moves(c6, b_ptr, (*b_ptr)[c6[1]][c6[0]].color, d6, w_castle);
                show_board(config[2], b_ptr, b6, NULL, theme);
                int* d7 = get_move(NULL, config[2]);
                make_move(d7, c6, b6, b_ptr, reset_p, w_castle);
                show_board(config[2], b_ptr, NULL, NULL, theme);

                sleep(5);
                break;

            //Options
            case 5:
                options_menu(config[0], config[1], config[2], theme);
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
