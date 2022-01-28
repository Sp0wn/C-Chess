#ifndef IO_H
#define IO_H

void show_logo();
int main_menu(char* lang);
void options_menu(char* lang, char* color, char* piece);
char** load_config();
void clear_config_cache(char** ptr);

#endif
