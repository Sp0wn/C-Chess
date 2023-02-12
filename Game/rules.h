#ifndef RULES_H
#define RULES_H

#include "../Game/piece.h"

int pawn_move(int* origin_xy, int* move_xy, char p_color, piece (*obj)[8][8]);

int** legal_moves(int* origin_xy, piece (*obj)[8][8], char p_color);

#endif
