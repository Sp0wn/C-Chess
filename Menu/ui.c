#include "ui.h"

#include <stdio.h>

#define BLUE    "\x1b[34m"
#define GREEN   "\x1b[32m"
#define RESET   "\x1b[0m"

void show_logo()
{
  //Function to show the app logo
  char line1[] = "   _____             _____ _";
  char line2[] = "  / ____|           / ____| |"
  "                      __";
  char line3[] = " | |       ______  | |    | |"
  "__   ___  ___ ___    (  )";
  char line4[] = " | |      |______| | |    |"
  " '_ \\ / _ \\/ __/ __|    ||";
  char line5[] = " | |____           | |____|"
  " | | |  __/\\__ \\__ \\   /__\\";
  char line6[] = "  \\_____|           \\_____|"
  "_| |_|\\___||___/___/  (____)";

  printf(BLUE);
  printf("%s\n", line1);
  printf("%s\n", line2);
  printf("%s\n", line3);
  printf("%s\n", line4);
  printf("%s\n", line5);
  printf("%s\n\n", line6);
  printf(RESET);
}

void show_main_menu_en()
{
  //Function to show the initial menu
  //in English
  printf(GREEN);
  printf("[1]: Player vs player online\n");
  printf("[2]: Player vs player local\n");
  printf("[3]: Player vs computer\n");
  printf("[4]: Free practice\n");
  printf("[5]: Options\n\n");
  printf(RESET);
}
