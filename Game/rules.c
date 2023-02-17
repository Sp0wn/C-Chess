#include "rules.h"

#include "../Game/piece.h"

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int pawn_move(int* origin_xy, int* move_xy, char p_color, piece (*obj)[8][8])
{
    //Pawn can't move to the same square of a friendly piece
    if((*obj)[move_xy[1]][move_xy[0]].name != ' ' && (*obj)[move_xy[1]][move_xy[0]].color == p_color) {
        return 0;
    } else {
        //Pawn can capture pieces in the next squares in diagonal
        if((abs(move_xy[0] - origin_xy[0]) == 1 && abs(move_xy[1] - origin_xy[1]) == 1) && (*obj)[move_xy[1]][move_xy[0]].name != ' ') {
            return 1;
        //Pawn can move between columns or move more than 2 squares
        } else if(origin_xy[0] != move_xy[0] || abs(move_xy[1] - origin_xy[1]) > 2) {
            return 0;
        } else {
            //Pawn can move 2 squares if it hasn't move
            if(abs(move_xy[1] - origin_xy[1]) == 2 && origin_xy[1] == 1) {
                return 1;
            } else if(abs(move_xy[1] - origin_xy[1]) == 2 && origin_xy[1] == 6) {
                return 1;
            } else if(abs(move_xy[1] - origin_xy[1]) == 2) {
                return 0;
            } else {
                //Pawn can't move backwards
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

int knight_move(int* origin_xy, int* move_xy, char p_color, piece (*obj)[8][8])
{
    //Knight can't move to the same square of a friendly piece
    if((*obj)[move_xy[1]][move_xy[0]].name != ' ' && (*obj)[move_xy[1]][move_xy[0]].color == p_color) {
        return 0;
    } else {
        //Knight can move in L
        if(abs(move_xy[0] - origin_xy[0]) == 1 && abs(move_xy[1] - origin_xy[1]) == 2) {
            return 1;
        } else if(abs(move_xy[0] - origin_xy[0]) == 2 && abs(move_xy[1] - origin_xy[1]) == 1) {
            return 1;
        } else {
            return 0;
        }
    }
}

int bishop_move(int *origin_xy, int *move_xy, char p_color, piece (*obj)[8][8])
{
    int diff, x_diff, y_diff;
    //Bishop can't move to the same square of a friendly piece
    if((*obj)[move_xy[1]][move_xy[0]].name != ' ' && (*obj)[move_xy[1]][move_xy[0]].color == p_color) {
        return 0;
    } else {
        //Bishop can move in diagonal
        if(abs(origin_xy[0] - move_xy[0]) == abs(origin_xy[1] - move_xy[1])) {
            //Trace the diagonal and search for any piece in the middle
            for(diff = abs(origin_xy[0] - move_xy[0]); diff > 1; diff--) {
                x_diff = (diff - 1) * ((move_xy[0] - origin_xy[0]) / abs(move_xy[0] - origin_xy[0]));
                y_diff = (diff - 1) * ((move_xy[1] - origin_xy[1]) / abs(move_xy[1] - origin_xy[1]));
                //Bishop can't go across pieces
                if((*obj)[move_xy[1] - y_diff][move_xy[0] - x_diff].name != ' ') {
                    return 0;
                }
            }
            return 1;
        } else {
            return 0;
        }
    }
}

int rook_move(int *origin_xy, int *move_xy, char p_color, piece (*obj)[8][8])
{
    int diff, real_diff;
    //Rook can't move to the same square of a friendly piece
    if((*obj)[move_xy[1]][move_xy[0]].name != ' ' && (*obj)[move_xy[1]][move_xy[0]].color == p_color) {
        return 0;
    } else {
        //Rook can move horizontally
        if(move_xy[0] != origin_xy[0] && move_xy[1] == origin_xy[1]) {
            //Trace the line and search for any piece in the middle
            for(diff = abs(origin_xy[0] - move_xy[0]); diff > 1; diff--) {
                real_diff = (diff - 1) * ((move_xy[0] - origin_xy[0]) / abs(move_xy[0] - origin_xy[0]));
                if((*obj)[move_xy[1]][move_xy[0] - real_diff].name != ' ') {
                    return 0;
                }
            }
            return 1;
        //Rook can move vertically
        } else if(move_xy[1] != origin_xy[1] && move_xy[0] == origin_xy[0]) {
            for(diff = abs(origin_xy[1] - move_xy[1]); diff > 1; diff--) {
                real_diff = (diff - 1) * ((move_xy[1] - origin_xy[1]) / abs(move_xy[1] - origin_xy[1]));
                if((*obj)[move_xy[1] - real_diff][move_xy[0]].name != ' ') {
                    return 0;
                }
            }
            return 1;
        } else {
            return 0;
        }
    }
}   

int** legal_moves(int* origin_xy, piece (*obj)[8][8], char p_color)
{
    int row, column, n_moves, legal;
    int* move;
    int** moves;
    int move_xy[2];

    moves = NULL;
    n_moves = 0;

    char symbol = (*obj)[origin_xy[1]][origin_xy[0]].name;
    //Search for possibilities around all the board
    for(row = 0; row < 8; row++) {
        for(column = 0; column < 8; column++) {
            //Sets values to pass to functions
            move_xy[1] = row;
            move_xy[0] = column;
            //Checks for piece type
            if(symbol == 'P' || symbol == 'p') {
                legal = pawn_move(origin_xy, move_xy, p_color, obj);
            } else if(symbol == 'N' || symbol == 'n') {
                legal = knight_move(origin_xy, move_xy, p_color, obj);
            } else if(symbol == 'B' || symbol == 'b') {
                legal = bishop_move(origin_xy, move_xy, p_color, obj);
            } else if(symbol == 'R' || symbol == 'r') {
                legal = rook_move(origin_xy, move_xy, p_color, obj);
            }

            if (legal == 1) {
                //Allocates for move coordinates
                move = malloc(2 * sizeof(int));
                move[1] = row;
                move[0] = column;
                //Allocates for move array
                moves = realloc(moves, (n_moves + 2) * sizeof(int*));
                moves[n_moves + 1] = move;
                n_moves++;
            }
        }
    }

    //Allocates array size in the first address
    int* size = malloc(1 * sizeof(int));
    size[0] = n_moves;
    moves[0] = size;

    return (moves+1);
}
