#ifndef RULES_H
#define RULES_H

#include "../Game/piece.h"
#include "../UI/Board.h"

int pawn_move(int* origin_xy, int* move_xy, char p_color, piece (*obj)[8][8]);
int knight_move(int* origin_xy, int* move_xy, char p_color, piece (*obj)[8][8]);
int bishop_move(int* origin_xy, int* move_xy, char p_color, piece (*obj)[8][8]);
int rook_move(int* origin_xy, int* move_xy, char p_color, piece (*obj)[8][8]);
int king_move(int* origin_xy, int* move_xy, char p_color, piece (*obj)[8][8], int* castle);

int piece_pinned(int* origin_xy, char line, char p_color, piece (*obj)[8][8]);
int** square_attacked(int* origin_xy, char p_color, int** old_arr, piece (*obj)[8][8]);

int** legal_moves(int* origin_xy, piece (*obj)[8][8], char p_color, int** attackers, int* castle, int* king, int** old_arr, piece blank);

#endif
