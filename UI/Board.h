#ifndef BOARD_H
#define BOARD_H

#include "../Game/piece.h"

void show_board(char* color, piece (*obj)[8][8], int** moves);

int* get_move(int* old_xy, char* color);
void make_move(int* move_xy, int* origin_xy, piece (*obj)[8][8], piece blank);

#endif
