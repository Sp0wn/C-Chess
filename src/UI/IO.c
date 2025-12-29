//File guard
#include "../../include/UI/IO.h"

//Include util functions
#include "../../include/UI/ui_utils.h"

//Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
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

//Shows the logo to the screen
void show_logo(GameTheme* theme, bool do_animation) {
}

//Loads into memory the menu strings
MainMenu* load_main_menu(MainMenu* old, char* lang) {
    int i;
    FILE* fptr;
    MainMenu* mainMenu;
    char section[16], key[32], value[64], buff[128];

    //Deallocates old menu
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
        memset(value, 0, 64);

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

//Loads into memory the menu strings
OptionsMenu* load_options_menu(OptionsMenu* old, char* lang) {
    int i, j;
    FILE* fptr;
    OptionsMenu* optionsMenu;
    char section[16], key[32], value[64], buff[128];;

    //Deallocates old menu
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
        memset(value, 0, 64);

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

//Loads into memory the variables for the option menu
OptionsVariables* load_options_variables(OptionsVariables* old, GameConfig* config) {
    int i, j;
    FILE* fptr;
    OptionsVariables* optionsVariables;
    char section[16], key[32], value[64], buff[128];;

    //Deallocates old struct
    free(old);

    //Opens file and handles errors
    fptr = open_file("/.C-Chess/options_variables.ini");

    //Allocates memory for the struct
    optionsVariables = malloc(sizeof(OptionsVariables));
    if(optionsVariables == NULL) {
        if(stdscr != NULL) {
            endwin();
        }
        perror("Could not allocate memory");
        exit(EXIT_FAILURE);
    }

    //Sets to zero strings
    memset(optionsVariables->selected_variable1, 0, 4);
    memset(optionsVariables->selected_variable2, 0, 2);
    memset(optionsVariables->selected_variable3, 0, 8);
    memset(optionsVariables->selected_variable4, 0, 2);

    //Sets selected variables
    strncpy(optionsVariables->selected_variable1, config->lang, 4);
    strncpy(optionsVariables->selected_variable2, config->theme, 2);
    strncpy(optionsVariables->selected_variable3, config->style, 8);
    strncpy(optionsVariables->selected_variable4, config->side, 2);

    //Links strings to internal array
    optionsVariables->variables_list[0] = optionsVariables->selected_variable1;
    optionsVariables->variables_list[1] = optionsVariables->selected_variable2;
    optionsVariables->variables_list[2] = optionsVariables->selected_variable3;
    optionsVariables->variables_list[3] = optionsVariables->selected_variable4;

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
        memset(value, 0, 64);

        //Splits key and value variables
        tokenize_config(key, value, buff);

        //Compares string with option to be read
        if(strncmp(section, "option1", 16) == 0) {
            if(strncmp(key, "variable1", 32) == 0) {
                strncpy(optionsVariables->option1_variables[0], value, 4);
            } else if(strncmp(key, "variable2", 32) == 0) {
                strncpy(optionsVariables->option1_variables[1], value, 4);
            } else if(strncmp(key, "variable3", 32) == 0) {
                strncpy(optionsVariables->option1_variables[2], value, 4);
            }

        } else if(strncmp(section, "option2", 16) == 0) {
            if(strncmp(key, "variable1", 32) == 0) {
                strncpy(optionsVariables->option2_variables[0], value, 2);
            } else if(strncmp(key, "variable2", 32) == 0) {
                strncpy(optionsVariables->option2_variables[1], value, 2);
            } else if(strncmp(key, "variable3", 32) == 0) {
                strncpy(optionsVariables->option2_variables[2], value, 2);
            }

        } else if(strncmp(section, "option3", 16) == 0) {
            if(strncmp(key, "variable1", 32) == 0) {
                strncpy(optionsVariables->option3_variables[0], value, 8);
            } else if(strncmp(key, "variable2", 32) == 0) {
                strncpy(optionsVariables->option3_variables[1], value, 8);
            }

        } else if(strncmp(section, "option4", 16) == 0) {
            if(strncmp(key, "variable1", 32) == 0) {
                strncpy(optionsVariables->option4_variables[0], value, 2);
            } else if(strncmp(key, "variable2", 32) == 0) {
                strncpy(optionsVariables->option4_variables[1], value, 2);
            }
        } 
    }

    //Closes gracefully the file
    fclose(fptr);

    return optionsVariables;
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

GameTheme* load_game_theme(GameTheme* old, char* sel_theme) {
    GameTheme* gameTheme;

    //Deallocates old theme
    free(old);

    //Allocates memory for the struct
    gameTheme = malloc(sizeof(GameTheme));
    if(gameTheme == NULL) {
        if(stdscr != NULL) {
            endwin();
        }
        perror("Could not allocate memory");
        exit(EXIT_FAILURE);
    }

    //Assigns colors codes based on the theme
    if(strncmp(sel_theme, "1", 2) == 0) {
        gameTheme->color_white = 1;
        gameTheme->color_text = 2;
        gameTheme->color_black = 3;
    } else if(strncmp(sel_theme, "2", 2) == 0) {
        gameTheme->color_white = 4;
        gameTheme->color_text = 5;
        gameTheme->color_black = 6;
    } else if(strncmp(sel_theme, "3", 2) == 0) {
        gameTheme->color_white = 7;
        gameTheme->color_text = 8;
        gameTheme->color_black = 9;
    }

    return gameTheme;
}
