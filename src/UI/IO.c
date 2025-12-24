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

//Loads into memory the menu strings
MainMenu* load_main_menu(MainMenu* old, char* lang) {
    int i, j;
    FILE* fptr;
    MainMenu* mainMenu;
    char main_menu_path[64], buff[128];
    char section[16], key[32], value[32];

    //Deallocates old configuration
    free(old);

    //Searches for the user directory
    //$HOME/.C-Chess/logo.txt
    strcpy(main_menu_path, getenv("HOME"));
    strcat(main_menu_path, "/.C-Chess/main_menu.ini");

    //Tries to open main menu file and manages errors 
    fptr = fopen(main_menu_path, "r");
    if(fptr == NULL) {
        if(stdscr != NULL) {
            endwin();
        }
        perror("Could not open logo file");
        exit(EXIT_FAILURE);
    }

    //Allocates memory for the struct
    mainMenu = malloc(sizeof(MainMenu));
    if(mainMenu == NULL) {
        perror("Could not allocate memory");
        exit(EXIT_FAILURE);
    }

    //Sets to zero strings
    memset(mainMenu->option1, 0, 64);
    memset(mainMenu->option2, 0, 64);
    memset(mainMenu->option3, 0, 64);
    memset(mainMenu->option4, 0, 64);
    memset(mainMenu->option5, 0, 64);

    //Links strings to internal array
    mainMenu->option_list[0] = mainMenu->option1;
    mainMenu->option_list[1] = mainMenu->option2;
    mainMenu->option_list[2] = mainMenu->option3;
    mainMenu->option_list[3] = mainMenu->option4;
    mainMenu->option_list[4] = mainMenu->option5;

    //Initializes strings
    memset(key, 0, 32);
    memset(value, 0, 32);
    memset(section, 0, 16);

    //Reads each option as a string
    while(fgets(buff, sizeof(buff), fptr)) {
        //Initializes iterators
        i = j = 0;

        //Searches for the section
        if(buff[i] == '[') {
            //Starts reading the section
            i++;
            memset(section, 0, 16);

            //Parses the section
            while(buff[i] != ']') {
                section[i - 1] = buff[i];
                i++;
            }
            section[i - 1] = '\0';
            continue;
        }

        //Checks for invalid lines
        if(buff[0] == ' ' || buff[0] == '\n' || buff[0] == '\0') {
            continue;
        }

        //Checks if the string is empty
        if(section[0] == 0) {
            continue;
        }

        //Cleans strings
        memset(key, 0, 32);
        memset(value, 0, 32);

        //Compares string with selected language
        if(strcmp(section, lang) == 0) {
            //Parses the key
            while(buff[i] != '=') {
                key[i] = buff[i];
                i++;
            }
            key[i] = '\0';

            //Parses the value
            while(buff[i + 1 + j] != '\n') {
                value[j] = buff[i + 1 + j];
                j++;
            }
            value[j] = '\0';

            //Assigns saved value to structure
            if(strcmp(key, "option1") == 0) {
                strcpy(mainMenu->option1, value);
            } else if(strcmp(key, "option2") == 0) {
                strcpy(mainMenu->option2, value);
            } else if(strcmp(key, "option3") == 0) {
                strcpy(mainMenu->option3, value);
            } else if(strcmp(key, "option4") == 0) {
                strcpy(mainMenu->option4, value);
            } else if(strcmp(key, "option5") == 0) {
                strcpy(mainMenu->option5, value);
            }
        }
    }

    //Closes gracefully the file
    fclose(fptr);

    return mainMenu;
}

//Loads into memory the game configurations
GameConfig* load_game_config(GameConfig* old) {
    int i, j;
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
    
    //Tries to open game config file and manages errors 
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
        i = j = 0;
        memset(key, 0, 8);
        memset(value, 0, 8);

        //Parses the key
        while(buff[i] != '=') {
            key[i] = buff[i];
            i++;
        }
        key[i] = '\0';

        //Parses the value
        while(buff[i + 1 + j] != '\n') {
            value[j] = buff[i + 1 + j];
            j++;
        }
        value[j] = '\0';

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
