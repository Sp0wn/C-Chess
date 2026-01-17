//File guard
#include "../../include/Game/rules.h"

//Libraries
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

bool pawn_move(int* origin_xy, int* target_xy, Board* board) {
    char target_piece = (*board)[target_xy[1]][target_xy[0]].name;
    char target_color = (*board)[target_xy[1]][target_xy[0]].color;
    char origin_piece = (*board)[origin_xy[1]][origin_xy[0]].name;
    char origin_color = (*board)[origin_xy[1]][origin_xy[0]].color;

    int x_diff = abs(target_xy[0] - origin_xy[0]);
    int y_diff = abs(target_xy[1] - origin_xy[1]);

    //Can not move to a square with a friendly piece
    if(target_piece != ' ' && target_color == origin_color) {
        return false;
    }

    //Can not move backwards
    if(origin_color == 'w' && target_xy[1] < origin_xy[1]) {
        return false;
    } else if(origin_color == 'b' && target_xy[1] > origin_xy[1]) {
        return false;
    }

    //Can capture close diagonal squares
    if((x_diff == 1 && y_diff == 1) && target_piece != ' ') {
        return true;
    } else if(x_diff >= 1) {
        return false;
    }

    //Can move one square upwards
    if(y_diff == 1 && target_piece == ' ') {
        return true;
    }

    //Can move two squares if has not moved
    if(y_diff == 2 && (origin_color == 'w' && origin_xy[1] == 1)) {
        if((*board)[target_xy[1] - 1][target_xy[0]].name != ' ') {
            return false;
        }
        return true;

    } else if(y_diff == 2 && (origin_color == 'b' && origin_xy[1] == 6)) {
        if((*board)[target_xy[1] + 1][target_xy[0]].name != ' ') {
            return false;
        }
        return true;

    //Can not move between columns or more than one square
    } else if(origin_xy[0] != target_xy[0] || y_diff >= 2) {
        return false;
    }

    return false;
}

bool rook_move(int* origin_xy, int* target_xy, Board* board) {
    char target_piece = (*board)[target_xy[1]][target_xy[0]].name;
    char target_color = (*board)[target_xy[1]][target_xy[0]].color;
    char origin_piece = (*board)[origin_xy[1]][origin_xy[0]].name;
    char origin_color = (*board)[origin_xy[1]][origin_xy[0]].color;

    int diff, dir, trace;

    //Can not move to a square with a friendly piece
    if(target_piece != ' ' && target_color == origin_color) {
        return false;
    }

    //Can move horizontally
    if(target_xy[0] != origin_xy[0] && target_xy[1] == origin_xy[1]) {
        diff = abs(target_xy[0] - origin_xy[0]);
        dir = (target_xy[0] - origin_xy[0]) / diff;

        //Traces line
        for(diff = diff; diff > 1; diff--) {
            trace = target_xy[0] - (diff - 1) * dir;
            
            //Can not go across pieces
            if((*board)[target_xy[1]][trace].name != ' ') {
                return false;
            }
        }
        return true;

    //Can move vertically
    } else if(target_xy[1] != origin_xy[1] && target_xy[0] == origin_xy[0]) {
        diff = abs(target_xy[1] - origin_xy[1]);
        dir = (target_xy[1] - origin_xy[1]) / diff;

        for(diff = diff; diff > 1; diff--) {
            trace = target_xy[1] - (diff - 1) * dir;
            
            if((*board)[trace][target_xy[0]].name != ' ') {
                return false;
            }
        }
        return true;
    } else {
        return false;
    }

    return false;
}

bool queen_move(int* origin_xy, int* target_xy, Board* board) {
    if(bishop_move(origin_xy, target_xy, board)) {
        return true;
    } else if(rook_move(origin_xy, target_xy, board)) {
        return true;
    } else {
        return false;
    }

    return false;
}
bool bishop_move(int* origin_xy, int* target_xy, Board* board) {
    char target_piece = (*board)[target_xy[1]][target_xy[0]].name;
    char target_color = (*board)[target_xy[1]][target_xy[0]].color;
    char origin_piece = (*board)[origin_xy[1]][origin_xy[0]].name;
    char origin_color = (*board)[origin_xy[1]][origin_xy[0]].color;
 
    int x_diff = abs(target_xy[0] - origin_xy[0]);
    int y_diff = abs(target_xy[1] - origin_xy[1]);

    int x_dir, y_dir;
    int diff, trace_xy[2];

    //Can not move to a square with a friendly piece
    if(target_piece != ' ' && target_color == origin_color) {
        return false;
    }

    //Can move in diagonals
    if(x_diff == y_diff) {
        x_dir = (target_xy[0] - origin_xy[0]) / x_diff;
        y_dir = (target_xy[1] - origin_xy[1]) / y_diff;
        //Traces diagonal
        for(diff = x_diff; diff > 1; diff--) {
            trace_xy[0] = target_xy[0] - (diff - 1) * x_dir;
            trace_xy[1] = target_xy[1] - (diff - 1) * y_dir;

            //Can not go across pieces
            if((*board)[trace_xy[1]][trace_xy[0]].name != ' ') {
                return false;
            }
        }
        return true;
    } else {
        return false;
    }

    return false;
}

bool knight_move(int* origin_xy, int* target_xy, Board* board) {
    char target_piece = (*board)[target_xy[1]][target_xy[0]].name;
    char target_color = (*board)[target_xy[1]][target_xy[0]].color;
    char origin_piece = (*board)[origin_xy[1]][origin_xy[0]].name;
    char origin_color = (*board)[origin_xy[1]][origin_xy[0]].color;
 
    int x_diff = abs(target_xy[0] - origin_xy[0]);
    int y_diff = abs(target_xy[1] - origin_xy[1]);

    //Can not move to a square with a friendly piece
    if(target_piece != ' ' && target_color == origin_color) {
        return false;
    }

    //Can move in L
    if(x_diff == 1 && y_diff == 2) {
        return true;
    } else if(x_diff == 2 && y_diff == 1) {
        return true;
    } else {
        return false;
    }

    return false;
}

Moves* legal_moves(int* origin_xy, Board* board, Moves* old_moves) {
    int p;
    int* move;
    bool legal;
    Moves* moves;
    int row, column, target_xy[2];
    char origin_piece, origin_color;

    //Deallocates old struct
    if(old_moves != NULL) {
        for(p = 0; p < old_moves->size; p++) {
            free(old_moves->list[p]);
        }
        free(old_moves->list);
    }
    free(old_moves);

    //Allocates memory for the struct
    moves = malloc(sizeof(Moves));
    if(moves == NULL) {
        if(stdscr != NULL) {
            endwin();
        }
        perror("Could not allocate memory");
        exit(EXIT_FAILURE);
    }

    //Initializes variables
    moves->size = 0;
    moves->list = NULL;

    origin_piece = (*board)[origin_xy[1]][origin_xy[0]].name;
    origin_color = (*board)[origin_xy[1]][origin_xy[0]].color;

    legal = false;
    for(row = 0; row < 8; row++) {
        for(column = 0; column < 8; column++) {
            //Sets temporal target
            target_xy[1] = row;
            target_xy[0] = column;

            //Checks for the piece type
            if(origin_piece == 'P' || origin_piece == 'p') {
                legal = pawn_move(origin_xy, target_xy, board);
            } else if(origin_piece == 'N' || origin_piece == 'n') {
                legal = knight_move(origin_xy, target_xy, board);
            } else if(origin_piece == 'B' || origin_piece == 'b') {
                legal = bishop_move(origin_xy, target_xy, board);
            } else if(origin_piece == 'R' || origin_piece == 'r') {
                legal = rook_move(origin_xy, target_xy, board);
            } else if(origin_piece == 'Q' || origin_piece == 'q') {
                legal = queen_move(origin_xy, target_xy, board);
            }

            //Can not move if it is not a move within pieces rules
            if(legal == false) {
                continue;;
            }

            if(legal == true) {
                //Allocates memory for the move
                move = malloc(2 * sizeof(int));
                if(move == NULL) {
                    if(stdscr != NULL) {
                        endwin();
                    }
                    perror("Could not allocate memory");
                    exit(EXIT_FAILURE);
                }

                //Saves target coordinates to array
                move[1] = row;
                move[0] = column;

                //Allocates memory for the moves array
                moves->list = realloc(moves->list, (moves->size + 1) * sizeof(int*));
                if(moves->list == NULL) {
                    if(stdscr != NULL) {
                        endwin();
                    }
                    perror("Could not allocate memory");
                    exit(EXIT_FAILURE);
                }

                //Saves move array to struct array
                moves->list[moves->size] = move;
                moves->size++;
            }
        }
    }

    if(moves->size > 0) {
        return moves;
    } else {
        free(moves);
        return NULL;
    }
}
