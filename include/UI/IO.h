#ifndef IO_H
#define IO_H

#include "mainmenu.h"
#include "optionsmenu.h"
#include "optionsvariables.h"
#include "gameconfig.h"
#include "gametheme.h"

#include <stdbool.h>

//Maximum dimensions of logo
#define LOGO_WIDTH 54
#define LOGO_HEIGHT 6

//Size of borders
#define BOX_BORDER 1

//Height of main menu
#define MAIN_MENU_SIZE 5

//Height of options menu
#define OPTIONS_MENU_SIZE 4

//Key codes
#define ESC 27
#define ENTER 10

char* load_logo(void);
void show_logo(GameTheme* theme, bool do_animation, char* logo);

MainMenu* load_main_menu(MainMenu* old, char* lang);
int show_main_menu(MainMenu* mainMenu, char* lang, GameTheme* theme);

OptionsMenu* load_options_menu(OptionsMenu* old, char* lang);
void show_options_menu(OptionsMenu* optionsMenu, OptionsVariables* vars, char* lang, GameTheme* theme);

OptionsVariables* load_options_variables(OptionsVariables* old, GameConfig* config);

void save_game_config(OptionsVariables* vars);
GameConfig* load_game_config(GameConfig* old);

GameTheme* load_game_theme(GameTheme* old, char* sel_theme);

#endif
