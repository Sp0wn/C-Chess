//Interface functions
#include "UI/IO.h"
#include "UI/Board.h"

//Game functions
#include "Game/set.h"
#include "Game/rules.h"

#include "Game/piece.h"

//Standard libraries
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
                show_board(config[2], b_ptr, NULL);
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
