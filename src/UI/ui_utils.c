//File guard
#include "../../include/UI/ui_utils.h"

#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

FILE* open_file(char* file) {
    FILE* fptr;
    char file_path[64];

    //Tries to get the home variable
    if(getenv("HOME") == NULL) {
        if(stdscr != NULL) {
            endwin();
        }
        fprintf(stderr, "Could not get the home variable\n");
        exit(EXIT_FAILURE);
    }

    //Initializes path string
    memset(file_path, 0, 64);

    //Searches for the user directory
    //$HOME/$FILE_PATH/$FILE
    strncpy(file_path, getenv("HOME"), 64);
    strncat(file_path, file, 32);

    //Tries to open the file
    fptr = fopen(file_path, "r");
    if(fptr == NULL) {
        if(stdscr != NULL) {
            endwin();
        }
        perror("Could not open file");
        exit(EXIT_FAILURE);
    }

    return fptr;
}

void init_config_tokens(char* key, char* value, char* section) {
    //Sets to zero all bytes
    memset(key, 0, 32);
    memset(value, 0, 64);
    memset(section, 0, 16);
}

void tokenize_config(char *key, char *value, char* buffer) {
    int i, j;
    i = j = 0;

    //Parses the key
    while(buffer[i] != '=') {
        key[i] = buffer[i];
        i++;
    }
    key[i] = '\0';

    //Parses the value
    while(buffer[i + 1 + j] != '\n') {
        value[j] = buffer[i + 1 + j];
        j++;
    }
    value[j] = '\0';
}
