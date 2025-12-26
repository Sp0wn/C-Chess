#ifndef IO_H
#define IO_H

#include "../../include/UI/mainmenu.h"
#include "../../include/UI/optionsmenu.h"
#include "../../include/UI/optionsvariables.h"
#include "../../include/UI/gameconfig.h"

char* load_logo(void);

MainMenu* load_main_menu(MainMenu* old, char* lang);

OptionsMenu* load_options_menu(OptionsMenu* old, char* lang);

OptionsVariables* load_options_variables(OptionsVariables* old, GameConfig* config);

GameConfig* load_game_config(GameConfig* old);

#endif
