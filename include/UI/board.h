#ifndef BOARD_H
#define BOARD_H

#include "gametheme.h"
#include "gameconfig.h"

#include "../../include/Game/piece.h"
#include "../../include/Game/moves.h"

#include <stdbool.h>
#include <ncurses.h>

//Board codes
#define BOARD_UP "_______________________________"
#define BOARD_DOWN "‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾"
#define BOARD_SPACE "|---|---|---|---|---|---|---|---|"

//Maximum dimensions of board
#define BOARD_WIDTH 36
#define BOARD_HEIGHT 18

void show_board(Board* board, GameConfig* config, GameTheme* theme, Moves* moves);
int show_piece(Board* board, int row, int column, char* style);
void show_moves(Board* board, GameConfig* config, GameTheme* theme, WINDOW* win, Moves* moves, int row, int column);

int* get_move(int* old_xy, char* side);
bool make_move(Board* board, int* origin_xy, int* target_xy, Moves* moves);

#endif
