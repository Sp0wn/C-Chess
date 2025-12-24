#ifndef IO_H
#define IO_H

#include "../../include/UI/mainmenu.h"
#include "../../include/UI/gameconfig.h"

char* load_logo(void);

MainMenu* load_main_menu(MainMenu* old, char* lang);

GameConfig* load_game_config(GameConfig* old);

#endif
