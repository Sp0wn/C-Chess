#ifndef UI_UTILS_H
#define UI_UTILS_H

#include <stdio.h>

FILE* open_file(char* file, char* flag);

void init_config_tokens(char* key, char* value, char* section);

void tokenize_config(char* key, char* value, char* buffer);

#endif
