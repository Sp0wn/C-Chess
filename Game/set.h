#ifndef SET_H
#define SET_H

#include "piece.h"

void set_color(piece (*obj)[8][8]);
void set_enpassant(piece (*obj)[8][8]);

void set_rooks(piece (*obj)[8][8]);
void set_knights(piece (*obj)[8][8]);
void set_bishops(piece (*obj)[8][8]);
void set_pawns(piece (*obj)[8][8]);
void set_queens(piece (*obj)[8][8]);
void set_kings(piece (*obj)[8][8]);
void set_blank(piece (*obj)[8][8]);

void set_pieces(piece (*obj)[8][8]);

void read_FEN(piece (*obj)[8][8], char* FEN);
char* write_FEN(piece (*obj)[8][8]);

#endif
