#include "UI/IO.h"
#include "UI/Board.h"

#include "Game/set.h"
#include "Game/move.h"

#include "Game/piece.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <locale.h>

#include <unistd.h>

#include <ncurses.h>

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

    //Sets locale
    char* locale;
    locale = setlocale(LC_ALL, "");

    //Starts main window
    initscr();
    raw();
    noecho();
    start_color();
    use_default_colors();
    init_pair(1, COLOR_BLUE, -1);
    init_pair(2, COLOR_GREEN, -1);
    init_pair(3, COLOR_RED, -1);
    curs_set(FALSE);

    run = 1;

    while(run) {
        show_logo();
        option = main_menu(config[0]);
        switch(option) {
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
                show_logo();
                set_pieces(config[2], b_ptr);
                show_board(config[2], b_ptr);
                get_move();
                break;

            case 5:
                options_menu(config[0], config[1], config[2]);
                clear_config_cache(config);
                config = load_config();
                break;
        }
    }

    endwin();
    clear_config_cache(config);

    return 0;
}
