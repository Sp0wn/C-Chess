#include "input.h"

#include <stdio.h>

#define RED     "\x1b[31m"
#define YELLOW  "\x1b[33m"
#define RESET   "\x1b[0m"

int input_menu()
{
  //Function to get user input
  //for the menu option
  int input;
  int done = 0;

  char prompt[] = "> ";
  char err[] = "Invalid option";

  while(!done) {
    printf(YELLOW);
    printf("%s", prompt);
    printf(RESET);
    //Validates if integer
    if(scanf("%d", &input) != 1) {
      printf(RED);
      printf("%s\n", err);
      printf(RESET);
      //Flush input buffer
      while(getchar() != '\n');
    } else {
      //Validates number range
      if(input >=1 && input <= 5) {
        done = 1;
      } else {
        printf(RED);
        printf("%s\n", err);
        printf(RESET);
        }
      }
  }
  return input;
}
