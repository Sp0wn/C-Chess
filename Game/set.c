#include "set.h"

#include "piece.h"

#include <stdio.h>
#include <stdlib.h>

#define RED     "\x1b[31m"
#define RESET   "\x1b[0m"

void set_color(char color, piece (*obj)[8][8])
{
  //Function to set the color of the pieces
  int r;
  int c;

  switch(color) {
    case 'w':
      for(r = 0;r < 8; r++) {
        for(c = 0; c < 8; c++) {
          if(r == 0 || r == 1) {
            (*obj)[r][c].color = 'w';
          } else if(r == 6 || r == 7) {
            (*obj)[r][c].color = 'b';
          }
        }
      }
      break;
    case 'b':
      for(r = 0; r < 8; r++) {
        for(c = 0; c < 8; c++) {
          if(r == 0 || r == 1) {
            (*obj)[r][c].color = 'b';
          } else if(r == 6 || r == 7) {
            (*obj)[r][c].color = 'w';
          }
        }
      }
      break;
    default:
      printf(RED);
      printf("Err: No color was set\n");
      printf(RESET);
      exit(1);
  }
}

void set_rooks(char color, piece (*obj)[8][8]) {
  if(color == 'w') {
    (*obj)[0][0].name = 'R';
    (*obj)[0][7].name = 'R';
    (*obj)[7][0].name = 'r';
    (*obj)[7][7].name = 'r';
  } else {
    (*obj)[0][0].name = 'r';
    (*obj)[0][7].name = 'r';
    (*obj)[7][0].name = 'R';
    (*obj)[7][7].name = 'R';
  }
}

void set_knights(char color, piece (*obj)[8][8]) {  
  if(color == 'w') {
    (*obj)[0][1].name = 'N';
    (*obj)[0][6].name = 'N';
    (*obj)[7][1].name = 'n';
    (*obj)[7][6].name = 'n';
  } else {
    (*obj)[0][1].name = 'n';
    (*obj)[0][6].name = 'n';
    (*obj)[7][1].name = 'N';
    (*obj)[7][6].name = 'N';
  }
}

void set_bishops(char color, piece (*obj)[8][8]) {  
  if(color == 'w') {
    (*obj)[0][2].name = 'B';
    (*obj)[0][5].name = 'B';
    (*obj)[7][2].name = 'b';
    (*obj)[7][5].name = 'b';
  } else {
    (*obj)[0][2].name = 'b';
    (*obj)[0][5].name = 'b';
    (*obj)[7][2].name = 'B';
    (*obj)[7][5].name = 'B';
  }

}

void set_pawns(char color, piece (*obj)[8][8]) {
  int s;
  
  if(color == 'w') {
    for(s = 0; s < 8; s++) {
      (*obj)[1][s].name = 'P';
    }
    for(s = 0; s < 8; s++) {
      (*obj)[6][s].name = 'p';
    }
  } else {
    for(s = 0; s < 8; s++) {
      (*obj)[1][s].name = 'p';
    }
    for(s = 0; s < 8; s++) {
      (*obj)[6][s].name = 'P';
    }
  }  
}

void set_queens(char color, piece (*obj)[8][8]) {
  if(color == 'w') {
    (*obj)[0][3].name = 'Q';
    (*obj)[7][3].name = 'q';
  } else {
    (*obj)[0][4].name = 'q';
    (*obj)[7][4].name = 'Q';
  }
}

void set_kings(char color, piece (*obj)[8][8]) {
  if(color == 'w') {
    (*obj)[0][4].name = 'K';
    (*obj)[7][4].name = 'k';
  } else {
    (*obj)[0][3].name = 'k';
    (*obj)[7][3].name = 'K';
  }
}

void set_blank(piece (*obj)[8][8]) {
  for(int r = 3; r < 6; r++) {
    for(int i = 0; i < 8; i++) {
      (*obj)[r][i].name = ' ';
    }
  }
}
