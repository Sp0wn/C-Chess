#ifndef RULES_H
#define RULES_H

#include "piece.h"

#include <stdbool.h>

bool pawn_move(int* origin_xy, int* target_xy, Board* board);
bool rook_move(int* origin_xy, int* target_xy, Board* board);
bool queen_move(int* origin_xy, int* target_xy, Board* board);
bool bishop_move(int* origin_xy, int* target_xy, Board* board);
bool knight_move(int* origin_xy, int* target_xy, Board* board);

#endif
