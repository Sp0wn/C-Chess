#ifndef BOARD_H
#define BOARD_H

#include "gametheme.h"
#include "gameconfig.h"

#include "../../include/Game/piece.h"

//Board codes
#define BOARD_UP "_______________________________"
#define BOARD_DOWN "‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾"
#define BOARD_SPACE "|---|---|---|---|---|---|---|---|"

//Maximum dimensions of board
#define BOARD_WIDTH 36
#define BOARD_HEIGHT 18

void show_board(Board* board, GameConfig* config, GameTheme* theme);
int show_piece(Board* board, int row, int column, char* style);

int* get_move(int* old_xy, char* side);

#endif
