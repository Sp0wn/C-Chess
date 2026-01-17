//Interface functions
#include "include/UI/IO.h"
#include "include/UI/board.h"

//Game functions
#include "include/Game/set.h"

//Standard Libraries
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <locale.h>

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

int main(void) {
    char* locale;
    locale = setlocale(LC_ALL, "");

    Board board;
    Board* board_ptr;
    board_ptr = &board;
    set_pieces(board_ptr);

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

    char* logo_ptr = load_logo();
    GameConfig* config_ptr = load_game_config(NULL);
    GameTheme* theme_ptr = load_game_theme(NULL, config_ptr->theme);
    
    show_logo(theme_ptr, true, logo_ptr);

    MainMenu* main_menu_ptr = load_main_menu(NULL, config_ptr->lang);
    show_main_menu(main_menu_ptr, config_ptr->lang, theme_ptr);

    clear();
    show_logo(theme_ptr, false, logo_ptr);

    OptionsMenu* options_menu_ptr = load_options_menu(NULL, config_ptr->lang);
    OptionsVariables* variables_ptr = load_options_variables(NULL, config_ptr);
    show_options_menu(options_menu_ptr, variables_ptr, config_ptr->lang, theme_ptr);

    clear();
    refresh();

    show_board(board_ptr, config_ptr, theme_ptr);

    int* xy = get_move(NULL, config_ptr->side);

    endwin();

    return 0;
} 
