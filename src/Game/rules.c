//File guard
#include "../../include/Game/rules.h"

//Libraries
#include <stdbool.h>
#include <stdlib.h>

bool pawn_move(int* origin_xy, int* target_xy, Board* board) {
    char move_piece = (*board)[target_xy[1]][target_xy[0]].name;
    char move_color = (*board)[target_xy[1]][target_xy[0]].color;
    char origin_piece = (*board)[origin_xy[1]][origin_xy[0]].name;
    char origin_color = (*board)[origin_xy[1]][origin_xy[0]].color;

    int x_diff = abs(target_xy[0] - origin_xy[0]);
    int y_diff = abs(target_xy[1] - origin_xy[1]);

    //Can not move to a square with a friendly piece
    if(move_piece != ' ' && move_color == origin_color) {
        return false;
    }

    //Can not move backwards
    if(origin_color == 'w' && target_xy[1] < origin_xy[1]) {
        return false;
    } else if(origin_color == 'b' && target_xy[1] > origin_xy[1]) {
        return false;
    }

    //Can capture close diagonal squares
    if((x_diff == 1 && y_diff == 1) && move_piece != ' ') {
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

    return true;
}

bool bishop_move(int* origin_xy, int* target_xy, Board* board) {
    char move_piece = (*board)[target_xy[1]][target_xy[0]].name;
    char move_color = (*board)[target_xy[1]][target_xy[0]].color;
    char origin_piece = (*board)[origin_xy[1]][origin_xy[0]].name;
    char origin_color = (*board)[origin_xy[1]][origin_xy[0]].color;
 
    int x_diff = abs(target_xy[0] - origin_xy[0]);
    int y_diff = abs(target_xy[1] - origin_xy[1]);

    int x_dir = (target_xy[0] - origin_xy[0]) / x_diff;
    int y_dir = (target_xy[1] - origin_xy[1]) / y_diff;

    int diff, trace_xy[2];

    //Can not move to a square with a friendly piece
    if(move_piece != ' ' && move_color == origin_color) {
        return false;
    }

    //Can move in diagonals
    if(x_diff == y_diff) {
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

    return true;
}

bool knight_move(int* origin_xy, int* target_xy, Board* board) {
    char move_piece = (*board)[target_xy[1]][target_xy[0]].name;
    char move_color = (*board)[target_xy[1]][target_xy[0]].color;
    char origin_piece = (*board)[origin_xy[1]][origin_xy[0]].name;
    char origin_color = (*board)[origin_xy[1]][origin_xy[0]].color;
 
    int x_diff = abs(target_xy[0] - origin_xy[0]);
    int y_diff = abs(target_xy[1] - origin_xy[1]);

    //Can not move to a square with a friendly piece
    if(move_piece != ' ' && move_color == origin_color) {
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

    return true;
}
