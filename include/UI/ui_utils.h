#ifndef UI_UTILS_H
#define UI_UTILS_H

#include "gametheme.h"
#include "optionsvariables.h"

#include <stdio.h>
#include <ncurses.h>

FILE* open_file(char* file, char* flag);

void init_config_tokens(char* key, char* value, char* section);

void init_vars_indexes(OptionsVariables* vars, int* var1, int* var2, int* var3, int* var4);

void tokenize_config(char* key, char* value, char* buffer);

void write_token(char* key, char* value, FILE* fptr);

void turn_on_color(WINDOW* win, int color_code);
void turn_off_color(WINDOW* win, int color_codeGame);

#endif
