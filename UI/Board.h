#ifndef BOARD_H
#define BOARD_H

#include "../Game/piece.h"
#include "../Game/set.h"

void show_board(char* color, piece (*obj)[8][8], int** moves, int* last_move, int* theme, int* king, char c_win, char* style);
int show_promotion(int* theme, piece (*obj)[8][8], char p_color, int column, char* color_direction);
int show_piece(int row, int column, char* style, piece (*obj)[8][8]);

int* get_move(int* old_xy, char* color);
int make_move(int* move_xy, int* origin_xy, int** legal_moves, piece (*obj)[8][8], piece blank, int* castle, int* king);
void undo_move(int* move_xy, int* origin_xy, piece (*obj)[8][8], piece blank, int* new_castle, int* old_castle, int* king, int* enpassant, char old_p);
int make_promotion(int option, int* origin_xy, piece (*obj)[8][8], char p_color);

int* search_enpassant(piece (*obj)[8][8]);

#endif
