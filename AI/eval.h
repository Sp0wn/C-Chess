#ifndef EVAL_H
#define EVAL_H

#include "../Game/piece.h"
#include "../Game/rules.h"

int eval_material(piece (*obj)[8][8], char color);
int check_checkmate(piece (*obj)[8][8], char color, piece blank, int* castle);

#endif
