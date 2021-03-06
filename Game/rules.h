#ifndef RULES_H
#define RULES_H

#include "../Game/piece.h"

int pawn_move(int* origin_xy, int* move_xy, piece (*obj)[8][8]);

int** legal_moves(int* origin_xy, piece (*obj)[8][8]);

#endif
