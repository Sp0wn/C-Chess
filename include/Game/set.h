#ifndef SET_H
#define SET_H

#include "piece.h"

void set_pawns(Board* board);
void set_rooks(Board* board);
void set_kings(Board* board);
void set_queens(Board* board);
void set_bishops(Board* board);
void set_knights(Board* board);

void set_pieces_color(Board* board);
void set_pieces_empty(Board* board);

void set_pieces(Board* board);

#endif
