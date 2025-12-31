//File guard
#include "../../include/UI/IO.h"

//Include util functions
#include "../../include/UI/ui_utils.h"

//Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <ncurses.h>

//Maximum dimensions of logo
#define LOGO_H 6
#define LOGO_W 54

//Size of borders
#define BOX_BORDER 1

//Height of main menu
#define MAIN_MENU_SIZE 5

//Key codes
#define ESC 27
#define ENTER 10

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
    logo = calloc(size + 1, sizeof(char));
    if(logo == NULL) {
        if(stdscr != NULL) {
            endwin();
        }
        perror("Could not allocate memory");
        exit(EXIT_FAILURE);
    }
    //Reads the entire logo into the buffer
    fread(logo, 1, size, fptr);
    //Adds terminator
    logo[size] = '\0';

    //Closes gracefully the file
    fclose(fptr);

    return logo;
}

//Displays the logo to the screen
void show_logo(GameTheme* theme, bool do_animation, char* logo) {
    int i, x, y, x_offset;

    //Gets the starting point for the logo
    x_offset = (getmaxx(stdscr) / 2) - (LOGO_W / 2);

    clear();

    attron(COLOR_PAIR(theme->color_white));

    i = x = 0;
    //Prints each line
    for(y = 0; y < 6; y++) {
        x = 0;
        //Prints each character
        while(logo[i] != '\n' && logo[i] != '\0') {
            mvaddch(y, x + x_offset, logo[i]);
            x++;
            i++;
        }

        //Checks if it is still inside array bounds
        if(logo[i] != '\0') {
            i++;
        }

        //Adds a delay of 0.25s for a simple animation
        if(do_animation == true) {
            refresh();
            usleep(250000);
        }
    }

    attroff(COLOR_PAIR(theme->color_white));

    refresh();
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
    memset(mainMenu->opt1, 0, 64);
    memset(mainMenu->opt2, 0, 64);
    memset(mainMenu->opt3, 0, 64);
    memset(mainMenu->opt4, 0, 64);
    memset(mainMenu->opt5, 0, 64);

    //Links strings to internal array
    mainMenu->opt_list[0] = mainMenu->opt1;
    mainMenu->opt_list[1] = mainMenu->opt2;
    mainMenu->opt_list[2] = mainMenu->opt3;
    mainMenu->opt_list[3] = mainMenu->opt4;
    mainMenu->opt_list[4] = mainMenu->opt5;

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
                strncpy(mainMenu->opt1, value, 64);
            } else if(strncmp(key, "option2", 32) == 0) {
                strncpy(mainMenu->opt2, value, 64);
            } else if(strncmp(key, "option3", 32) == 0) {
                strncpy(mainMenu->opt3, value, 64);
            } else if(strncmp(key, "option4", 32) == 0) {
                strncpy(mainMenu->opt4, value, 64);
            } else if(strncmp(key, "option5", 32) == 0) {
                strncpy(mainMenu->opt5, value, 64);
            }
        }
    }

    //Closes gracefully the file
    fclose(fptr);

    return mainMenu;
}

//Displays the interactive main menu
int show_main_menu(MainMenu* mainMenu, char* lang, GameTheme* theme) {
    bool done;
    int ch, option;
    int width, height;
    int i, x_offset, y_offset;

    //Defines size and starting points of window
    width = LOGO_W + 2*BOX_BORDER;
    height = MAIN_MENU_SIZE + 2*BOX_BORDER;
    x_offset = (getmaxx(stdscr) / 2) - (LOGO_W / 2);
    y_offset = LOGO_H + 1;

    //Creates window
    WINDOW* main_menu_win = newwin(height, width, y_offset, x_offset);
    if(main_menu_win == NULL) {
        endwin();
        fprintf(stderr, "Could not create new window\n");
        exit(EXIT_FAILURE);
    }

    //Adds attributes
    keypad(main_menu_win, TRUE);
    wattron(main_menu_win, COLOR_PAIR(theme->color_text));
    box(main_menu_win, 0, 0);

    //Main menu loop
    option = 1;
    done = false;
    while(done == false) {
        //Starts printing all options
        for(i = 0; i < 5; i++) {
            //Checks if selected option equals line
            if(option == (i + 1)) {
                wattron(main_menu_win, A_STANDOUT);
                mvwaddstr(main_menu_win, i + 1, 1, mainMenu->opt_list[i]);
                wattroff(main_menu_win, A_STANDOUT);
                continue;
            }
            mvwaddstr(main_menu_win, i + 1, 1, mainMenu->opt_list[i]);
        }
        wrefresh(main_menu_win);

        //Waits for input
        ch = wgetch(main_menu_win);

        switch(ch) {
            case ESC:
                option = 0;
                done = true;
                break;

            case KEY_UP:
                option = (option == 1) ? 5 : option - 1;
                break;

            case KEY_DOWN:
                option = (option == 5) ? 1 : option + 1;
                break;

            case ENTER:
                done = true;
                break;
        }
    }

    wattroff(main_menu_win, COLOR_PAIR(theme->color_text));

    //Deletes allocated window
    delwin(main_menu_win);

    return option;
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
    memset(optionsMenu->opt1, 0, 32);
    memset(optionsMenu->opt2, 0, 32);
    memset(optionsMenu->opt3, 0, 32);
    memset(optionsMenu->opt4, 0, 32);

    //Links strings to internal array
    optionsMenu->opt_list[0] = optionsMenu->opt1;
    optionsMenu->opt_list[1] = optionsMenu->opt2;
    optionsMenu->opt_list[2] = optionsMenu->opt3;
    optionsMenu->opt_list[3] = optionsMenu->opt4;

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
                strncpy(optionsMenu->opt1, value, 32);
            } else if(strncmp(key, "option2", 32) == 0) {
                strncpy(optionsMenu->opt2, value, 32);
            } else if(strncmp(key, "option3", 32) == 0) {
                strncpy(optionsMenu->opt3, value, 32);
            } else if(strncmp(key, "option4", 32) == 0) {
                strncpy(optionsMenu->opt4, value, 32);
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
    memset(optionsVariables->sel_var1, 0, 4);
    memset(optionsVariables->sel_var2, 0, 2);
    memset(optionsVariables->sel_var3, 0, 8);
    memset(optionsVariables->sel_var4, 0, 2);

    //Sets selected variables
    strncpy(optionsVariables->sel_var1, config->lang, 4);
    strncpy(optionsVariables->sel_var2, config->theme, 2);
    strncpy(optionsVariables->sel_var3, config->style, 8);
    strncpy(optionsVariables->sel_var4, config->side, 2);

    //Links strings to internal array
    optionsVariables->vars_list[0] = optionsVariables->sel_var1;
    optionsVariables->vars_list[1] = optionsVariables->sel_var2;
    optionsVariables->vars_list[2] = optionsVariables->sel_var3;
    optionsVariables->vars_list[3] = optionsVariables->sel_var4;

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
                strncpy(optionsVariables->opt1_vars[0], value, 4);
            } else if(strncmp(key, "variable2", 32) == 0) {
                strncpy(optionsVariables->opt1_vars[1], value, 4);
            } else if(strncmp(key, "variable3", 32) == 0) {
                strncpy(optionsVariables->opt1_vars[2], value, 4);
            }

        } else if(strncmp(section, "option2", 16) == 0) {
            if(strncmp(key, "variable1", 32) == 0) {
                strncpy(optionsVariables->opt2_vars[0], value, 2);
            } else if(strncmp(key, "variable2", 32) == 0) {
                strncpy(optionsVariables->opt2_vars[1], value, 2);
            } else if(strncmp(key, "variable3", 32) == 0) {
                strncpy(optionsVariables->opt2_vars[2], value, 2);
            }

        } else if(strncmp(section, "option3", 16) == 0) {
            if(strncmp(key, "variable1", 32) == 0) {
                strncpy(optionsVariables->opt3_vars[0], value, 8);
            } else if(strncmp(key, "variable2", 32) == 0) {
                strncpy(optionsVariables->opt3_vars[1], value, 8);
            }

        } else if(strncmp(section, "option4", 16) == 0) {
            if(strncmp(key, "variable1", 32) == 0) {
                strncpy(optionsVariables->opt4_vars[0], value, 2);
            } else if(strncmp(key, "variable2", 32) == 0) {
                strncpy(optionsVariables->opt4_vars[1], value, 2);
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
