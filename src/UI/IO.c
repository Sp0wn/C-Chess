#include "../../include/UI/IO.h"

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
        exit(1);
    }

    //Calculates file size
    fseek(fptr, 0, SEEK_END);
    size = ftell(fptr);
    fseek(fptr, 0, SEEK_SET);

    //Allocates the space for the buffer
    logo = malloc(size);

    //Reads the entire logo into the buffer
    fread(logo, 1, size, fptr);

    //Closes gracefully the file
    fclose(fptr);

    return logo;
}
