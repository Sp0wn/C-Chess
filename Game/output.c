void show_board(char color, piece (*obj)[8][8]) {
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
    for(int r = 7; r >= 0; r--) {
      printf("\n%i ", r + 1);
      for(int c = 0; c < 8; c++) {
        printf("%c ", (*obj)[r][c].name);
      }
    }
    printf("\n  ");
    for(int l = 0; l < 8; l++) {
      printf("%c ", columns[l]);
    }
  } else {
    for(int r = 7; r >= 0; r--) {
      printf("\n%i ", 8 - r);
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
