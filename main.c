#include "Menu/ui.h"
#include "Menu/input.h"

#include "Board/set.h"
#include "Board/piece.h"

#include <stdio.h>
#include <stdlib.h>

int main()
{
  piece board[8][8], (*b_ptr)[8][8];
  b_ptr = &board;
  char a = 'w';
  set_color(a, b_ptr);
  set_rooks(a, b_ptr);
  set_knights(a, b_ptr);
  set_bishops(a, b_ptr);
  set_pawns(a, b_ptr);
  set_blank(b_ptr);
  set_queens(a, b_ptr);
  set_kings(a, b_ptr);
  show_board(a, b_ptr);
  return 0;
}
