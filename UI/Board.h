#ifndef BOARD_H
#define BOARD_H

#include "../Game/piece.h"

void show_board(char* color, piece (*obj)[8][8]);
void get_move();

#endif
