#include "IO.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ncurses.h>

#define TIME 250000
#define ESC 27
#define ENTER 10

void show_logo(int* theme)
{
    //Function to show the app logo
    //in ASCII art
    
    int x, i;
    
    //Buffers individual lines in differents arrays
    char* line1 = "  _____             _____ _";
    char* line2 = " / ____|           / ____| |                      __";
    char* line3 = "| |       ______  | |    | |__   ___  ___ ___    (  )";
    char* line4 = "| |      |______| | |    | '_ \\ / _ \\/ __/ __|    ||";
    char* line5 = "| |____           | |____| | | |  __/\\__ \\__ \\   /__\\";
    char* line6 = " \\_____|           \\_____|_| |_|\\___||___/___/  (____)";
   
    //Store the logo lines in an array of pointers
    char* lines[6] = {line1, line2, line3, line4, line5, line6};

    //Get the middle of the screen
    x = getmaxx(stdscr);
    x = x / 2;
    x = x - 28;
    
    clear();

    attron(COLOR_PAIR(theme[0]));

    //Print logo with a little animation
    for(i = 0; i < 6; i++) {
        mvprintw(i, x, "%s", lines[i]);
        refresh();
        usleep(TIME);
    }

    attroff(COLOR_PAIR(theme[0]));

    refresh();
}

void options_menu(char* lang, char* color, char* piece, int* theme)
{
    //Function to show the options menu
    // after option 5

    int x, y;
    getmaxyx(stdscr, y, x);
    WINDOW* win = newwin(7, 56, 7, (x / 2 - 28));
    keypad(win, TRUE);

    int option, ch, done, i;
    int var1, var2, var3;

    //Struct for the options strings
    struct N_Options {
        char option1[32];
        char option2[32];
        char option3[32];
        char* allOptions[5];
    };

    //Struct for the options variables
    struct V_Options {
        char variable1[4];
        char variables1[3][3];
        char variable2[2];
        char variables2[3][2];
        char variable3[2];
        char variables3[2][2];
        char* allVariables[3];
    };

    //Set the strings accordingly to the language
    struct N_Options Menu_Options;
    if(strcmp(lang, "en") == 0) {
        strcpy(Menu_Options.option1, "[1]: Language = ");
        strcpy(Menu_Options.option2, "[2]: Color = ");
        strcpy(Menu_Options.option3, "[3]: Pieces = ");
    } else if(strcmp(lang, "es") == 0) {
        strcpy(Menu_Options.option1, "[1]: Idioma = ");
        strcpy(Menu_Options.option2, "[2]: Color = ");
        strcpy(Menu_Options.option3, "[3]: Piezas = ");
    } else if(strcmp(lang, "de") == 0) {
        strcpy(Menu_Options.option1, "[1]: Sprache = ");
        strcpy(Menu_Options.option2, "[2]: Farbe = ");
        strcpy(Menu_Options.option3, "[3]: Stuecke = ");
    }

    //Track the options
    Menu_Options.allOptions[0] = Menu_Options.option1;
    Menu_Options.allOptions[1] = Menu_Options.option2;
    Menu_Options.allOptions[2] = Menu_Options.option3;

    //Set the possibles variables for each option
    struct V_Options Menu_Variables;
    strcpy(Menu_Variables.variable1, lang);
    strcpy(Menu_Variables.variable2, color);
    strcpy(Menu_Variables.variable3, piece);

    strcpy(Menu_Variables.variables1[0], "en");
    strcpy(Menu_Variables.variables1[1], "es");
    strcpy(Menu_Variables.variables1[2], "de");

    strcpy(Menu_Variables.variables2[0], "1");
    strcpy(Menu_Variables.variables2[1], "2");
    strcpy(Menu_Variables.variables2[2], "3");

    strcpy(Menu_Variables.variables3[0], "W");
    strcpy(Menu_Variables.variables3[1], "B");

    //Track the variables
    Menu_Variables.allVariables[0] = Menu_Variables.variable1;
    Menu_Variables.allVariables[1] = Menu_Variables.variable2;
    Menu_Variables.allVariables[2] = Menu_Variables.variable3;

    wattron(win, COLOR_PAIR(theme[1]));
    box(win, 0, 0);

    option = 1;

    done = 0;

    var1 = 1;
    var2 = 1;
    var3 = 1;

    while(!(done)) {
        for(i = 1; i < 4; i++) {
            if(option == i) {
                wattron(win, A_STANDOUT);
                mvwprintw(win, i, 1, "%s", Menu_Options.allOptions[i - 1]);
                wprintw(win, "%s", Menu_Variables.allVariables[i - 1]);
                wattroff(win, A_STANDOUT);
                continue;
            }
            mvwprintw(win, i, 1, "%s", Menu_Options.allOptions[i - 1]);
            wprintw(win, "%s", Menu_Variables.allVariables[i - 1]);
        }
        wrefresh(win);

        ch = wgetch(win);

        switch(ch) {
            //Exit without saving
            case ESC:
                done = 1;
                break;

            case KEY_DOWN:
                option = (option == 3) ? 1 : option + 1;
                break;

            case KEY_UP:
                option = (option == 1) ? 3 : option - 1;
                break;

            //Exit and save the configuration
            case ENTER:
                done = 1;

                FILE* savefile;
                char config_dir[64];
                strcpy(config_dir, getenv("HOME"));
                strcat(config_dir, "/.config/C-Chess.config");
                savefile = fopen(config_dir, "w");

                fputs(Menu_Variables.allVariables[0], savefile);
                fputs("\n", savefile);
                fputs(Menu_Variables.allVariables[1], savefile);
                fputs("\n", savefile);
                fputs(Menu_Variables.allVariables[2], savefile);
                fputs("\n", savefile);

                fclose(savefile);
                break;

            case KEY_LEFT:
                switch(option) {
                    case 1:
                        var1 = (var1 == 1) ? 3 : var1 - 1;
                        strcpy(Menu_Variables.variable1, Menu_Variables.variables1[var1 - 1]);
                        break;

                    case 2:
                        var2 = (var2 == 1) ? 3 : var2 - 1;
                        strcpy(Menu_Variables.variable2, Menu_Variables.variables2[var2 - 1]);
                        break;

                    case 3:
                        var3 = (var3 == 1) ? 2 : var3 - 1;
                        strcpy(Menu_Variables.variable3, Menu_Variables.variables3[var3 - 1]);
                        break;
                }
                break;

            case KEY_RIGHT:
                switch(option) {
                    case 1:
                        var1 = (var1 == 3) ? 1 : var1 + 1;
                        strcpy(Menu_Variables.variable1, Menu_Variables.variables1[var1 - 1]);
                        break;

                    case 2:
                        var2 = (var2 == 3) ? 1 : var2 + 1;
                        strcpy(Menu_Variables.variable2, Menu_Variables.variables2[var2 - 1]);
                        break;

                    case 3:
                        var3 = (var3 == 2) ? 1 : var3 + 1;
                        strcpy(Menu_Variables.variable3, Menu_Variables.variables3[var3 - 1]);
                        break;
                }
                break;
        }
    }

    wattroff(win, COLOR_PAIR(2));
    delwin(win);
}

int main_menu(char* lang, int* theme)
{
    //Function to show the initial menu
    
    int x, y;
    getmaxyx(stdscr, y, x);
    WINDOW* win = newwin(7, 56, 7, (x / 2 - 28));
    keypad(win, TRUE);

    int option, ch, done, i;

    struct N_Options {
        char option1[36];
        char option2[36];
        char option3[36];
        char option4[36];
        char option5[36];
        char* allOptions[5];
    };

    //Defines a struct for storing the options and track it's index
    struct N_Options Menu_Options;
    if(strcmp(lang, "en") == 0) {
        strcpy(Menu_Options.option1, "[1]: Player vs player online");
        strcpy(Menu_Options.option2, "[2]: Player vs player local");
        strcpy(Menu_Options.option3, "[3]: Player vs computer");
        strcpy(Menu_Options.option4, "[4]: Free practice");
        strcpy(Menu_Options.option5, "[5]: Options");
    } else if(strcmp(lang, "es") == 0) {
        strcpy(Menu_Options.option1, "[1]: Jugador vs jugador en linea");
        strcpy(Menu_Options.option2, "[2]: Jugador vs jugador local");
        strcpy(Menu_Options.option3, "[3]: Jugador vs computadora");
        strcpy(Menu_Options.option4, "[4]: Practica libre");
        strcpy(Menu_Options.option5, "[5]: Opciones"); 
    } else if(strcmp(lang, "de") == 0) {
        strcpy(Menu_Options.option1, "[1]: Spieler vs Spieler online");
        strcpy(Menu_Options.option2, "[2]: Spieler vs Spieler lokal");
        strcpy(Menu_Options.option3, "[3]: Spieler vs computer");
        strcpy(Menu_Options.option4, "[4]: Freies training");
        strcpy(Menu_Options.option5, "[5]: Optionen"); 
    }

    Menu_Options.allOptions[0] = Menu_Options.option1;
    Menu_Options.allOptions[1] = Menu_Options.option2;
    Menu_Options.allOptions[2] = Menu_Options.option3;
    Menu_Options.allOptions[3] = Menu_Options.option4;
    Menu_Options.allOptions[4] = Menu_Options.option5;

    wattron(win, COLOR_PAIR(theme[1]));
    box(win, 0, 0);

    option = 1;

    done = 0;

    while(!(done)) {
        for(i = 1; i < 6; i++) {
            if(option == i) {
                wattron(win, A_STANDOUT);
                mvwprintw(win, i, 1, "%s", Menu_Options.allOptions[i - 1]);
                wattroff(win, A_STANDOUT);
                continue;
            }
            mvwprintw(win, i, 1, "%s", Menu_Options.allOptions[i - 1]);
        }
        wrefresh(win);

        ch = wgetch(win);

        switch (ch) {
            //Set the option flag to 0 so the programs exits
            case ESC:
                done = 1;
                option = 0;
                break;

            case KEY_DOWN:
                option = (option == 5) ? 1 : option + 1;
                break;

            case KEY_UP:
                option = (option == 1) ? 5 : option - 1;
                break;

            //Exit the function and continue with the saved
            //option variable
            case ENTER:
                done = 1;
                break;
        }
    }

    wattroff(win, COLOR_PAIR(2));
    delwin(win);
    return option;
}

char** load_config()
{
    //Function to load the
    //C-chess config file

    //Start and allocate memory for
    //the pointer of array of pointers to chars
    char** config;
    config = malloc(4 * sizeof(char*));

    //Start and allocate memory for
    //each array of pointers
    char* lang, *color, *piece;
    lang = malloc(4 * sizeof(char));
    color = malloc(4 * sizeof(char));
    piece = malloc(4 * sizeof(char));
    
    //Set pointers
    config[0] = lang;
    config[1] = color;
    config[2] = piece;

    FILE* configfile;
    char config_dir[64];
    strcpy(config_dir, getenv("HOME"));
    strcat(config_dir, "/.config/C-Chess.config");
    configfile = fopen(config_dir, "r");

    fgets(config[0], 4, (FILE*)configfile);
    config[0][strcspn(config[0], "\n")] = 0;

    fgets(config[1], 4, (FILE*)configfile);
    config[1][strcspn(config[1], "\n")] = 0;

    fgets(config[2], 4, (FILE*)configfile);
    config[2][strcspn(config[2], "\n")] = 0;

    fclose(configfile);
    
    return config;
}

int* load_theme(char *color)
{
    int* theme;
    theme = malloc(3 * sizeof(int));

    switch(color[0]) {
        case '1':
            theme[0] = 1;
            theme[1] = 2;
            theme[2] = 3;
            break;

        case '2':
            theme[0] = 4;
            theme[1] = 5;
            theme[2] = 6;
            break;

        case '3':
            theme[0] = 7;
            theme[1] = 8;
            theme[1] = 9;
            break;
    }

    return theme;
}

void clear_config_cache(char** ptr_c, int* ptr_t)
{
    //Function to deallocate
    //the memory from the old ptr

    free(ptr_c[0]);
    free(ptr_c[1]);
    free(ptr_c[2]);
    free(ptr_c);
    free(ptr_t);
}

