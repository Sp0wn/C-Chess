#ifndef IO_H
#define IO_H

#include "../../include/UI/mainmenu.h"
#include "../../include/UI/optionsmenu.h"
#include "../../include/UI/optionsvariables.h"
#include "../../include/UI/gameconfig.h"
#include "../../include/UI/gametheme.h"

#include <stdbool.h>

char* load_logo(void);
void show_logo(GameTheme* theme, bool do_animation, char* logo);

MainMenu* load_main_menu(MainMenu* old, char* lang);
int show_main_menu(MainMenu* mainMenu, char* lang, GameTheme* theme);

OptionsMenu* load_options_menu(OptionsMenu* old, char* lang);

OptionsVariables* load_options_variables(OptionsVariables* old, GameConfig* config);

void save_game_config(GameConfig* config);
GameConfig* load_game_config(GameConfig* old);

GameTheme* load_game_theme(GameTheme* old, char* sel_theme);

#endif
