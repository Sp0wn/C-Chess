#ifndef ENGINE_H
#define ENGINE_H

#include "../Game/piece.h"

#include "../Game/rules.h"
#include "../UI/Board.h"

#include "eval.h"

void play_random(piece (*obj)[8][8], char player, int* king, int* castle, piece blank);
int* fill_arr(int* old_arr, int size, int excluded);
float minimax(piece (*obj)[8][8], int* depth, int is_max, float alpha, float beta, piece blank, int* castle_w, int* castle_b, char color);
void play_engine(piece (*obj)[8][8], char player, int* king, int* castle_w, int* castle_b, piece blank, int* depth);

#endif
