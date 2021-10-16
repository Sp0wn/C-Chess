#include "output.h"

#include "piece.h"

#include <stdio.h>

void show_board(char color, piece (*obj)[8][8]) {
  //Function to show the current state of the board
  char columns[8] = {
    'a',
    'b',
    'c',
    'd',
    'e',
    'f',
    'g',
    'h'
  };

  if(color == 'w') {
    //Print columns
    for(int r = 7; r >= 0; r--) {
      printf("\n%i ", r + 1);
      //Print rows
      for(int c = 0; c < 8; c++) {
        printf("%c ", (*obj)[r][c].name);
      }
    }
    printf("\n  ");
    for(int l = 0; l < 8; l++) {
      printf("%c ", columns[l]);
    }
  } else {
    //Print columns
    for(int r = 7; r >= 0; r--) {
      printf("\n%i ", 8 - r);
      //Print rows
      for(int c = 0; c < 8; c++) {
        printf("%c ", (*obj)[r][c].name);
      }
    }
    printf("\n  ");
    for(int l = 0; l < 8; l++) {
      printf("%c ", columns[7 - l]);
    }
  }
  printf("\n");
}
