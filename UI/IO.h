#ifndef IO_H
#define IO_H

#include "../Game/clock.h"

void show_logo(int* theme, int animation);
int main_menu(char* lang, int* theme);
void options_menu(char* lang, char* color, char* piece, int* theme, char* style);
char** load_config();
void clear_config_cache(char** ptr_c, int* ptr_t);
int* load_theme(char* color);
void* load_clock(void* master_clock);
void set_time(M_clock* master_clock, int* theme);

#endif
