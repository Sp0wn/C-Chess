#ifndef BOARD_H
#define BOARD_H

#include "../Game/piece.h"

void show_board(char* color, piece (*obj)[8][8], int** moves, int* last_move, int* theme);
int show_promotion(int* theme, piece (*obj)[8][8], char p_color, int column);

int* get_move(int* old_xy, char* color);
int make_move(int* move_xy, int* origin_xy, int** legal_moves, piece (*obj)[8][8], piece blank);
int make_promotion(int option, int* origin_xy, piece (*obj)[8][8], char p_color);

#endif
