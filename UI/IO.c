//File guard
#include "IO.h"

//Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ncurses.h>
#include <pthread.h>

#include "../Game/clock.h"

//Time macro (2.5s)
#define TIME 250000

//Keyboard codes
#define ESC 27
#define ENTER 10

void show_logo(int* theme, int animation)
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
        if(animation == 1) {
            refresh();
            usleep(TIME);
        }
    }

    attroff(COLOR_PAIR(theme[0]));

    refresh();
}

void options_menu(char* lang, char* color, char* piece, int* theme, char* style)
{
    //Function to show the options menu
    //after option 5

    //Create the window menu
    //in the middle
    int x, y;
    getmaxyx(stdscr, y, x);
    WINDOW* win = newwin(7, 56, 7, (x / 2 - 28));
    keypad(win, TRUE);

    int option, ch, done, i;
    int var1, var2, var3, var4;

    //Struct for the options strings
    struct N_Options {
        char option1[32];
        char option2[32];
        char option3[32];
        char option4[32];
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
        char variable4[12];
        char variables4[2][12];
        char* allVariables[4];
    };

    //Set the strings accordingly to the language
    struct N_Options Menu_Options;
    if(strcmp(lang, "en") == 0) {
        strcpy(Menu_Options.option1, "[1]: Language = ");
        strcpy(Menu_Options.option2, "[2]: Color = ");
        strcpy(Menu_Options.option3, "[3]: Pieces = ");
        strcpy(Menu_Options.option4, "[4]: Style = ");
        var1 = 1;
    } else if(strcmp(lang, "es") == 0) {
        strcpy(Menu_Options.option1, "[1]: Idioma = ");
        strcpy(Menu_Options.option2, "[2]: Color = ");
        strcpy(Menu_Options.option3, "[3]: Piezas = ");
        strcpy(Menu_Options.option4, "[4]: Estilo = ");
        var1 = 2;
    } else if(strcmp(lang, "de") == 0) {
        strcpy(Menu_Options.option1, "[1]: Sprache = ");
        strcpy(Menu_Options.option2, "[2]: Farbe = ");
        strcpy(Menu_Options.option3, "[3]: Stuecke = ");
        strcpy(Menu_Options.option4, "[4]: Stil = ");
        var1 = 3;
    }

    //Set the variables accordingly to the options
    if(strcmp(color, "1") == 0) {
        var2 = 1;
    } else if(strcmp(color, "2") == 0) {
        var2 = 2;
    } else if(strcmp(color, "3") == 0) {
        var2 = 3;
    }

    //Set the variables accordingly to the options
    if(strcmp(piece, "W") == 0) {
        var3 = 1;
    } else if(strcmp(piece, "B") == 0) {
        var3 = 2;
    }

    if(strcmp(style, "ASCII  ") == 0) {
        var4 = 1;
    } else if(strcmp(style, "Unicode") == 0) {
        var4 = 2;
    }

    //Track the options
    Menu_Options.allOptions[0] = Menu_Options.option1;
    Menu_Options.allOptions[1] = Menu_Options.option2;
    Menu_Options.allOptions[2] = Menu_Options.option3;
    Menu_Options.allOptions[3] = Menu_Options.option4;

    //Set the possibles variables for each option
    struct V_Options Menu_Variables;
    strcpy(Menu_Variables.variable1, lang);
    strcpy(Menu_Variables.variable2, color);
    strcpy(Menu_Variables.variable3, piece);
    strcpy(Menu_Variables.variable4, style);

    strcpy(Menu_Variables.variables1[0], "en");
    strcpy(Menu_Variables.variables1[1], "es");
    strcpy(Menu_Variables.variables1[2], "de");

    strcpy(Menu_Variables.variables2[0], "1");
    strcpy(Menu_Variables.variables2[1], "2");
    strcpy(Menu_Variables.variables2[2], "3");

    strcpy(Menu_Variables.variables3[0], "W");
    strcpy(Menu_Variables.variables3[1], "B");

    strcpy(Menu_Variables.variables4[0], "ASCII  ");
    strcpy(Menu_Variables.variables4[1], "Unicode");

    //Track the variables
    Menu_Variables.allVariables[0] = Menu_Variables.variable1;
    Menu_Variables.allVariables[1] = Menu_Variables.variable2;
    Menu_Variables.allVariables[2] = Menu_Variables.variable3;
    Menu_Variables.allVariables[3] = Menu_Variables.variable4;

    wattron(win, COLOR_PAIR(theme[1]));
    box(win, 0, 0);

    option = 1;

    done = 0;

    //Starts printing the menu 
    //with a loop
    while(!(done)) {
        for(i = 1; i < 5; i++) {
            if(option == i) {
                //Highlights current option
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

        //Waits for keyboard input
        ch = wgetch(win);

        switch(ch) {
            //Exit without saving
            case ESC:
                done = 1;
                break;

            //Cycles between options
            case KEY_DOWN:
                option = (option == 4) ? 1 : option + 1;
                break;

            case KEY_UP:
                option = (option == 1) ? 4 : option - 1;
                break;

            //Exit and save the configuration
            case ENTER:
                done = 1;

                FILE* savefile;
                char config_dir[64];

                //Uses logic to get to the user file
                strcpy(config_dir, getenv("HOME"));
                strcat(config_dir, "/.config/C-Chess.config");
                savefile = fopen(config_dir, "w");

                fputs(Menu_Variables.allVariables[0], savefile);
                fputs("\n", savefile);
                fputs(Menu_Variables.allVariables[1], savefile);
                fputs("\n", savefile);
                fputs(Menu_Variables.allVariables[2], savefile);
                fputs("\n", savefile);
                fputs(Menu_Variables.allVariables[3], savefile);
                fputs("\n", savefile);

                fclose(savefile);
                break;

            //Cycles between variables
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

                    case 4:
                        var4 = (var4 == 1) ? 2 : var4 - 1;
                        strcpy(Menu_Variables.variable4, Menu_Variables.variables4[var4 - 1]);
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

                    case 4:
                        var4 = (var4 == 2) ? 1 : var4 + 1;
                        strcpy(Menu_Variables.variable4, Menu_Variables.variables4[var4 - 1]);
                        break;
                }
                break;
        }
    }

    wattroff(win, COLOR_PAIR(theme[1]));
    delwin(win);
}

int main_menu(char* lang, int* theme)
{
    //Function to show the initial menu
    
    int x, y;

    //Create the window menu
    //in the middle 
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

    //Starts printing the options
    //with a loop
    while(!(done)) {
        for(i = 1; i < 6; i++) {
            if(option == i) {
                //Highlights current option
                wattron(win, A_STANDOUT);
                mvwprintw(win, i, 1, "%s", Menu_Options.allOptions[i - 1]);
                wattroff(win, A_STANDOUT);
                continue;
            }
            mvwprintw(win, i, 1, "%s", Menu_Options.allOptions[i - 1]);
        }
        wrefresh(win);

        //Waits for keyboard input
        ch = wgetch(win);

        switch (ch) {
            //Set the option flag to 0 so the programs exits
            case ESC:
                done = 1;
                option = 0;
                break;

            //Cycles between options
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

    wattroff(win, COLOR_PAIR(theme[1]));
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
    char* lang, *color, *piece, *style;
    lang = malloc(4 * sizeof(char));
    color = malloc(4 * sizeof(char));
    piece = malloc(4 * sizeof(char));
    style = malloc(4 * sizeof(char));
    
    //Set pointers
    config[0] = lang;
    config[1] = color;
    config[2] = piece;
    config[3] = style;

    FILE* configfile;
    char config_dir[64];

    //Finds file with logic
    strcpy(config_dir, getenv("HOME"));
    strcat(config_dir, "/.config/C-Chess.config");
    configfile = fopen(config_dir, "r");

    //Copies content into array
    fgets(config[0], 4, (FILE*)configfile);
    config[0][strcspn(config[0], "\n")] = 0;

    fgets(config[1], 4, (FILE*)configfile);
    config[1][strcspn(config[1], "\n")] = 0;

    fgets(config[2], 4, (FILE*)configfile);
    config[2][strcspn(config[2], "\n")] = 0;

    fgets(config[3], 8, (FILE*)configfile);
    config[3][strcspn(config[3], "\n")] = 0;

    fclose(configfile);
    
    return config;
}

int* load_theme(char *color)
{
    //Function to load the
    //C-chess theme

    int* theme;

    //Sets space for pointer of array
    theme = malloc(3 * sizeof(int));

    //Loads different colors depending
    //the option
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

    //Config pointers
    free(ptr_c[0]);
    free(ptr_c[1]);
    free(ptr_c[2]);
    free(ptr_c[3]);

    //Config pointer
    free(ptr_c);

    //Theme pointer
    free(ptr_t);
}

void* load_clock(void* master_clock)
{
    //Gets struct and sets time variables
    M_clock* local_clock = (M_clock*)master_clock;
    int w_sec, w_min, b_sec, b_min;

    //Creates window
    int x, y;
    getmaxyx(stdscr, y, x);    
    WINDOW* win = newwin(3, 36, 26, (x / 2 - 18));
    box(win, 0, 0);

    //Neither clock has finished
    while(!(local_clock->end)) {
       //White turn
        if(local_clock->turn == 1) {
            local_clock->W_Clock = local_clock->W_Clock - 1;

        //Black turn
        } else {
            local_clock->B_Clock = local_clock->B_Clock - 1;
        }

        //Calculate individual time forms
        w_sec = local_clock->W_Clock % 60;
        w_min = local_clock->W_Clock / 60;
        b_sec = local_clock->B_Clock % 60;
        b_min = local_clock->B_Clock / 60;

        mvwprintw(win, 1, 1, "             ");
        if(w_min < 10) {
            mvwprintw(win, 1, 2, "%i", w_min);
        } else {
            mvwprintw(win, 1, 1, "%i", w_min);
        }
        mvwprintw(win, 1, 3, ":");
        if(w_sec < 10) {
            mvwprintw(win, 1, 5, "%i", w_sec);
        } else {
            mvwprintw(win, 1, 4, "%i", w_sec);
        }
        mvwprintw(win, 1, 7, "|");
        if(b_min < 10) {
            mvwprintw(win, 1, 10, "%i", b_min);
        } else {
            mvwprintw(win, 1, 9, "%i", b_min);
        }
        mvwprintw(win, 1, 11, ":");
        if(b_sec < 10) {
            mvwprintw(win, 1, 13, "%i", b_sec);
        } else {
            mvwprintw(win, 1, 12, "%i", b_sec);
        }
        wrefresh(win);

        if((local_clock->W_Clock == 0) || (local_clock->B_Clock == 0)) {
            local_clock->end = 1;
        }

        sleep(1);
    }

    return NULL;
}

void set_time(M_clock* master_clock, int* theme)
{
    int x, y, i;
    int position, done, ch;

    done = 0;
    position = 1;

    getmaxyx(stdscr, y, x);    
    WINDOW* win = newwin(3, 36, 7, (x / 2 - 18));
    keypad(win, TRUE);
    attron(COLOR_PAIR(theme[0]));
    box(win, 0, 0);
    attroff(COLOR_PAIR(theme[0]));

    int minute_format[2] = {0, 0};
    int seconds_format[2] = {0, 0};

    while(!done) {
        for(i = 1; i < 3; i++) {
            if(i == position) {
                wattron(win, A_STANDOUT);
                mvwprintw(win, 1, i, "%i", minute_format[i-1]);
                wattroff(win, A_STANDOUT);
                continue;
            }
            mvwprintw(win, 1, i, "%i", minute_format[i-1]);
        }
        wrefresh(win);

        ch = wgetch(win);
        
        switch(ch) {
            case KEY_UP:
                minute_format[position-1] = (minute_format[position-1] == 9) ? 0 : minute_format[position-1] + 1;
                break;

            case KEY_DOWN:
                minute_format[position-1] = (minute_format[position-1] == 0) ? 9 : minute_format[position-1] - 1;
                break;
            
            case KEY_LEFT:
                position = (position == 1) ? 2 : position - 1;
                break;

            case KEY_RIGHT:
                position = (position == 2) ? 1 : position + 1;
                break;

            case ENTER:
                done = 1;
                break;

        }
    }

    done = 0;
    position = 1;

    while(!done) {
        for(i = 4; i < 6; i++) {
            if(i == position+3) {
                wattron(win, A_STANDOUT);
                mvwprintw(win, 1, i, "%i", seconds_format[i-4]);
                wattroff(win, A_STANDOUT);
                continue;
            }
            mvwprintw(win, 1, i, "%i", seconds_format[i-4]);
        }
        wrefresh(win);

        ch = wgetch(win);
        
        switch(ch) {
            case KEY_UP:
                seconds_format[position-1] = (seconds_format[position-1] == 9) ? 0 : seconds_format[position-1] + 1;
                break;

            case KEY_DOWN:
                seconds_format[position-1] = (seconds_format[position-1] == 0) ? 9 : seconds_format[position-1] - 1;
                break;
            
            case KEY_LEFT:
                position = (position == 1) ? 2 : position - 1;
                break;

            case KEY_RIGHT:
                position = (position == 2) ? 1 : position + 1;
                break;

            case ENTER:
                done = 1;
                break;

        }
    }
    
    master_clock->W_Clock = ((minute_format[0]*10 + minute_format[1])*60)+(seconds_format[0]*10)+seconds_format[1];
    master_clock->B_Clock = ((minute_format[0]*10 + minute_format[1])*60)+(seconds_format[0]*10)+seconds_format[1];
}
