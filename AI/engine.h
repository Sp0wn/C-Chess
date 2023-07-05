#ifndef ENGINE_H
#define ENGINE_H

#include "../Game/piece.h"

#include "../Game/rules.h"
#include "../UI/Board.h"

void play_random(piece (*obj)[8][8], char player, int* king, int* castle, piece blank);
int* fill_arr(int* old_arr, int size, int excluded);
int minimax(piece (*obj)[8][8], int depth, int is_max);

#endif
