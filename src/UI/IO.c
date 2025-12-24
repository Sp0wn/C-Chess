//File guard
#include "../../include/UI/IO.h"

//Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

//Loads the logo dynamically
char* load_logo(void) {
    long size;
    FILE* fptr;
    char* logo;
    char logo_path[64];

    //Searches for the user directory
    //$HOME/.C-Chess/logo.txt
    strcpy(logo_path, getenv("HOME"));
    strcat(logo_path, "/.C-Chess/logo.txt");

    //Tries to open logo file and manages errors 
    fptr = fopen(logo_path, "r");
    if(fptr == NULL) {
        if(stdscr != NULL) {
            endwin();
        }
        perror("Could not open logo file");
        exit(EXIT_FAILURE);
    }

    //Calculates file size
    fseek(fptr, 0, SEEK_END);
    size = ftell(fptr);
    fseek(fptr, 0, SEEK_SET);

    //Allocates the space for the buffer
    logo = calloc(size, sizeof(char));
    if(logo == NULL) {
        perror("Could not allocate memory");
        exit(EXIT_FAILURE);
    }

    //Reads the entire logo into the buffer
    fread(logo, 1, size, fptr);

    //Closes gracefully the file
    fclose(fptr);

    return logo;
}

//Loads into memory the game configurations
GameConfig* load_config(GameConfig* old) {
    int i, k;
    FILE* fptr;
    GameConfig* gameConfig;
    char key[8], value[8];
    char game_config_path[64], buff[16];

    //Deallocates old configuration
    free(old);

    //Searches for the user directory
    //$HOME/.config/C-Chess/options.cfg
    strcpy(game_config_path, getenv("HOME"));
    strcat(game_config_path, "/.config/C-Chess/options.cfg");
    
    //Tries to open logo file and manages errors 
    fptr = fopen(game_config_path, "r");
    if(fptr == NULL) {
        if(stdscr != NULL) {
            endwin();
        }
        perror("Could not open logo file");
        exit(EXIT_FAILURE);
    }

    //Allocates memory for the struct
    gameConfig = malloc(sizeof(GameConfig));
    if(gameConfig == NULL) {
        perror("Could not allocate memory");
        exit(EXIT_FAILURE);
    }
    memset(gameConfig->lang, 0, 4);

    //Reads each configuration as a string
    while(fgets(buff, sizeof(buff), fptr)) {
        //Initializes loop variables
        i = k = 0;
        memset(key, 0, 8);
        memset(value, 0, 8);

        //Parses the key
        while(buff[i] != '=') {
            key[i] = buff[i];
            i++;
        }
        key[i] = '\0';

        //Parses the value
        while(buff[i + 1 + k] != '\n') {
            value[k] = buff[i + 1 + k];
            k++;
        }
        value[k] = '\0';

        //Assigns saved value to structure
        if(strcmp(key, "lang") == 0) {
            strcpy(gameConfig->lang, value);
        } else if(strcmp(key, "theme") == 0) {
            strcpy(gameConfig->theme, value);
        } else if(strcmp(key, "style") == 0) {
            strcpy(gameConfig->style, value);
        } else if(strcmp(key, "side") == 0) {
            strcpy(gameConfig->side, value);
        }
    }

    //Closes gracefully the file
    fclose(fptr);

    return gameConfig;
}
