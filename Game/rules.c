#include "rules.h"

#include "../Game/piece.h"

#include <stdio.h>
#include <stdlib.h>

int pawn_move(int* origin_xy, int* move_xy, char p_color, piece (*obj)[8][8])
{
    if((*obj)[move_xy[1]][move_xy[0]].name != ' ' && (*obj)[move_xy[1]][move_xy[0]].color == p_color) {
        return 0;
    } else {
        if((abs(move_xy[0] - origin_xy[0]) == 1 && abs(move_xy[1] - origin_xy[1]) == 1) && (*obj)[move_xy[1]][move_xy[0]].name != ' ') {
            return 1;
        } else if(origin_xy[0] != move_xy[0] || abs(move_xy[1] - origin_xy[1]) > 2) {
            return 0;
        } else {
            if(abs(move_xy[1] - origin_xy[1]) == 2 && origin_xy[1] == 1) {
                return 1;
            } else if(abs(move_xy[1] - origin_xy[1]) == 2 && origin_xy[1] == 6) {
                return 1;
            } else if(abs(move_xy[1] - origin_xy[1]) == 2) {
                return 0;
            } else {
                if((*obj)[origin_xy[1]][origin_xy[0]].color == 'w' && move_xy[1] < origin_xy[1]) {
                    return 0;
                } else if((*obj)[origin_xy[1]][origin_xy[0]].color == 'b' && move_xy[1] > origin_xy[1]) {
                    return 0;
                } else {
                    return 1;
                }
            }
        }
    }
}

int** legal_moves(int* origin_xy, piece (*obj)[8][8])
{
    int row, column;
    int* move;
    int** moves;
    int n_moves;
    int move_xy[2];

    moves = NULL;
    n_moves = 0;

    char symbol = (*obj)[origin_xy[1]][origin_xy[0]].name;
    for(row = 0; row < 8; row++) {
        for(column = 0; column < 8; column++) {
            move_xy[1] = row;
            move_xy[0] = column;
            if(symbol == 'P' || symbol == 'p') {
                if(pawn_move(origin_xy, move_xy, 'w', obj)) {
                    move = malloc(2 * sizeof(int));
                    move[1] = row;
                    move[0] = column;
                    printf("%i, %i\n", column, row);

                    moves = realloc(moves, (n_moves + 1) * sizeof(int*));
                    moves[n_moves] = move;
                    n_moves++;
                }
            }
        }
    }
    return moves;
}
