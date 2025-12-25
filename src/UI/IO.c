//File guard
#include "../../include/UI/IO.h"

//Include util functions
#include "../../include/UI/ui_utils.h"

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

    //Opens file and handles errors
    fptr = open_file("/.C-Chess/logo.txt");

    //Calculates file size
    fseek(fptr, 0, SEEK_END);
    size = ftell(fptr);
    fseek(fptr, 0, SEEK_SET);

    //Checks if the file is empty
    if(size <= 0) {
        if(stdscr != NULL) {
            endwin();
        }
        fprintf(stderr, "Corrupted file\n");
        exit(EXIT_FAILURE);
    }

    //Allocates the space for the buffer
    logo = calloc(size, sizeof(char));
    if(logo == NULL) {
        if(stdscr != NULL) {
            endwin();
        }
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
    int i;
    FILE* fptr;
    MainMenu* mainMenu;
    char section[16], key[32], value[32], buff[128];

    //Deallocates old configuration
    free(old);

    //Opens file and handles errors
    fptr = open_file("/.C-Chess/main_menu.ini");

    //Allocates memory for the struct
    mainMenu = malloc(sizeof(MainMenu));
    if(mainMenu == NULL) {
        if(stdscr != NULL) {
            endwin();
        }
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
    init_config_tokens(key, value, section);

    //Reads each option as a string
    while(fgets(buff, sizeof(buff), fptr)) {
        //Initializes iterators
        i = 0;

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
        if(strncmp(section, lang, 4) == 0) {
            //Splits key and value variables
            tokenize_config(key, value, buff);
            
            //Assigns saved value to structure
            if(strncmp(key, "option1", 32) == 0) {
                strncpy(mainMenu->option1, value, 64);
            } else if(strncmp(key, "option2", 32) == 0) {
                strncpy(mainMenu->option2, value, 64);
            } else if(strncmp(key, "option3", 32) == 0) {
                strncpy(mainMenu->option3, value, 64);
            } else if(strncmp(key, "option4", 32) == 0) {
                strncpy(mainMenu->option4, value, 64);
            } else if(strncmp(key, "option5", 32) == 0) {
                strncpy(mainMenu->option5, value, 64);
            }
        }
    }

    //Closes gracefully the file
    fclose(fptr);

    return mainMenu;
}

OptionsMenu* load_options_menu(OptionsMenu* old, char* lang) {
    int i, j;
    FILE* fptr;
    OptionsMenu* optionsMenu;
    char section[16], key[32], value[32], buff[128];;

    //Deallocates old configuration
    free(old);

    //Opens file and handles errors
    fptr = open_file("/.C-Chess/options_menu.ini");

    //Allocates memory for the struct
    optionsMenu = malloc(sizeof(OptionsMenu));
    if(optionsMenu == NULL) {
        if(stdscr != NULL) {
            endwin();
        }
        perror("Could not allocate memory");
        exit(EXIT_FAILURE);
    }

    //Sets to zero strings
    memset(optionsMenu->option1, 0, 32);
    memset(optionsMenu->option2, 0, 32);
    memset(optionsMenu->option3, 0, 32);
    memset(optionsMenu->option4, 0, 32);

    //Links strings to internal array
    optionsMenu->option_list[0] = optionsMenu->option1;
    optionsMenu->option_list[1] = optionsMenu->option2;
    optionsMenu->option_list[2] = optionsMenu->option3;
    optionsMenu->option_list[3] = optionsMenu->option4;

    //Initializes strings
    init_config_tokens(key, value, section);

    //Reads each option as a string
    while(fgets(buff, sizeof(buff), fptr)) {
        //Initializes iterators
        i = 0;

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
        if(strncmp(section, lang, 4) == 0) {
            //Splits key and value variables
            tokenize_config(key, value, buff);
            
            //Assigns saved value to structure
            if(strncmp(key, "option1", 32) == 0) {
                strncpy(optionsMenu->option1, value, 32);
            } else if(strncmp(key, "option2", 32) == 0) {
                strncpy(optionsMenu->option2, value, 32);
            } else if(strncmp(key, "option3", 32) == 0) {
                strncpy(optionsMenu->option3, value, 32);
            } else if(strncmp(key, "option4", 32) == 0) {
                strncpy(optionsMenu->option4, value, 32);
            }
        }
    }

    //Closes gracefully the file
    fclose(fptr);

    return optionsMenu;
}

//Loads into memory the game configurations
GameConfig* load_game_config(GameConfig* old) {
    int i;
    FILE* fptr;
    GameConfig* gameConfig;
    char key[8], value[8], buff[16];

    //Deallocates old configuration
    free(old);

    //Opens file and handles errors
    fptr = open_file("/.config/C-Chess/options.cfg");
    
    //Allocates memory for the struct
    gameConfig = malloc(sizeof(GameConfig));
    if(gameConfig == NULL) {
        if(stdscr != NULL) {
            endwin();
        }
        perror("Could not allocate memory");
        exit(EXIT_FAILURE);
    }
    memset(gameConfig->lang, 0, 4);

    //Reads each configuration as a string
    while(fgets(buff, sizeof(buff), fptr)) {
        //Initializes loop variables
        i = 0;
        memset(key, 0, 8);
        memset(value, 0, 8);

        //Checks for invalid lines
        if(buff[0] == ' ' || buff[0] == '\n' || buff[0] == '\0') {
            continue;
        }

        //Splits key and value variables
        tokenize_config(key, value, buff);

        //Assigns saved value to structure
        if(strncmp(key, "lang", 8) == 0) {
            strncpy(gameConfig->lang, value, 4);
        } else if(strncmp(key, "theme", 8) == 0) {
            strncpy(gameConfig->theme, value, 2);
        } else if(strncmp(key, "style", 8) == 0) {
            strncpy(gameConfig->style, value, 8);
        } else if(strncmp(key, "side", 8) == 0) {
            strncpy(gameConfig->side, value, 2);
        }
    }

    //Closes gracefully the file
    fclose(fptr);

    return gameConfig;
}
