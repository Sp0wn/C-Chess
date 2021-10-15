#ifndef SET_H
#define SET_H

#include "piece.h"

void set_color(char color, piece (*obj)[8][8]);

void set_rooks(char color, piece (*obj)[8][8]);
void set_knights(char color, piece (*obj)[8][8]);
void set_bishops(char color, piece (*obj)[8][8]);
void set_pawns(char color, piece (*obj)[8][8]);
void set_queens(char color, piece (*obj)[8][8]);
void set_kings(char color, piece (*obj)[8][8]);
void set_blank(piece (*obj)[8][8]);

void show_board(char color, piece (*obj)[8][8]);

#endif
