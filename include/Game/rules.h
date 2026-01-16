#ifndef RULES_H
#define RULES_H

#include "piece.h"

#include <stdbool.h>

bool pawn_move(int* origin_xy, int* move_xy, Board* board);
bool knight_move(int* origin_xy, int* move_xy, Board* board);

#endif
