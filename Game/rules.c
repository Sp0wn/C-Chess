#include "rules.h"

#include "../Game/piece.h"
#include "../UI/Board.h"

#include <curses.h>
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
        //Pawn can't move backwards
        if((*obj)[origin_xy[1]][origin_xy[0]].color == 'w' && move_xy[1] < origin_xy[1]) {
            return 0;
        } else if((*obj)[origin_xy[1]][origin_xy[0]].color == 'b' && move_xy[1] > origin_xy[1]) {
            return 0;            
        } else {
            //Pawn can capture pieces in the next squares in diagonal
            if((abs(move_xy[0] - origin_xy[0]) == 1 && abs(move_xy[1] - origin_xy[1]) == 1) && (*obj)[move_xy[1]][move_xy[0]].name != ' ') {
                return 1;
            //Pawn can en passant
            } else if((abs(move_xy[0] - origin_xy[0]) == 1 && abs(move_xy[1] - origin_xy[1]) == 1) && (*obj)[origin_xy[1]][move_xy[0]].enpassant == 1) {
                return 1;
            //Pawn can't move between columns or move more than 2 squares
            } else if(origin_xy[0] != move_xy[0] || abs(move_xy[1] - origin_xy[1]) > 2) {
                return 0;
            //Pawn can't capture vertically
            } else if((*obj)[move_xy[1]][move_xy[0]].name != ' ') {
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
    char king_symbol;
    king_symbol = (p_color == 'w') ? 'K' : 'k';
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
                if((*obj)[move_xy[1] - y_diff][move_xy[0] - x_diff].name != ' ' && (*obj)[move_xy[1] - y_diff][move_xy[0] - x_diff].name == king_symbol) {
                    return 0;
                } else if((*obj)[move_xy[1] - y_diff][move_xy[0] - x_diff].name != ' ' && (*obj)[move_xy[1] - y_diff][move_xy[0] - x_diff].name != king_symbol) {
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
    char king_symbol;
    king_symbol = (p_color == 'w') ? 'K' : 'k';
    //Rook can't move to the same square of a friendly piece
    if((*obj)[move_xy[1]][move_xy[0]].name != ' ' && (*obj)[move_xy[1]][move_xy[0]].color == p_color) {
        return 0;
    } else {
        //Rook can move horizontally
        if(move_xy[0] != origin_xy[0] && move_xy[1] == origin_xy[1]) {
            //Trace the line and search for any piece in the middle
            for(diff = abs(origin_xy[0] - move_xy[0]); diff > 1; diff--) {
                real_diff = (diff - 1) * ((move_xy[0] - origin_xy[0]) / abs(move_xy[0] - origin_xy[0]));
                if((*obj)[move_xy[1]][move_xy[0] - real_diff].name != ' ' && (*obj)[move_xy[1]][move_xy[0] - real_diff].name == king_symbol) {
                    return 0;
                } else if((*obj)[move_xy[1]][move_xy[0] - real_diff].name != ' ' && (*obj)[move_xy[1]][move_xy[0] - real_diff].name != king_symbol) {
                    return 0;
                }
            }
            return 1;
        //Rook can move vertically
        } else if(move_xy[1] != origin_xy[1] && move_xy[0] == origin_xy[0]) {
            for(diff = abs(origin_xy[1] - move_xy[1]); diff > 1; diff--) {
                real_diff = (diff - 1) * ((move_xy[1] - origin_xy[1]) / abs(move_xy[1] - origin_xy[1]));
                if((*obj)[move_xy[1] - real_diff][move_xy[0]].name != ' ' && (*obj)[move_xy[1] - real_diff][move_xy[0]].name == king_symbol) {
                    return 0;
                } else if((*obj)[move_xy[1] - real_diff][move_xy[0]].name != ' ' && (*obj)[move_xy[1] - real_diff][move_xy[0]].name != king_symbol) {
                    return 0;
                }
            }
            return 1;
        } else {
            return 0;
        }
    }
}

int king_move(int *origin_xy, int *move_xy, char p_color, piece (*obj)[8][8], int* castle)
{
    int pawn_left, pawn_right, direction, trace;
    int move_trace[2];
    int knights_square[8];
    //King can't move to the same square of a friendly piece
    if((*obj)[move_xy[1]][move_xy[0]].name != ' ' && (*obj)[move_xy[1]][move_xy[0]].color == p_color) {
        return 0;    
    } else {
        //King can only move in a range of one square
        if((move_xy[1] == origin_xy[1]) && (abs(move_xy[0] - origin_xy[0]) == 2)) {
            //King can't castle if in check
            if(square_attacked(origin_xy, p_color, NULL, obj) != NULL) {
                return 0; 
            }
            direction = (move_xy[0] - origin_xy[0]) / 2;
            move_trace[1] = origin_xy[1];
            //Short castling
            if(direction == 1) {
                if(castle[1] == 0) {
                    return 0;
                } else {
                    for(trace = 1; trace < 3; trace++) {
                        move_trace[0] = origin_xy[0] + trace;
                        if((*obj)[origin_xy[1]][origin_xy[0] + trace].name != ' ' || square_attacked(move_trace, p_color, NULL, obj) != NULL) {
                            return 0; 
                        }
                    }
                    return 1;
                }
            //Long castling
            } else {
                if(castle[0] == 0) {
                    return 0;
                } else {
                     for(trace = 1; trace < 4; trace++) {
                        move_trace[0] = origin_xy[0] - trace;
                        if((*obj)[origin_xy[1]][origin_xy[0] - trace].name != ' ' || square_attacked(move_trace, p_color, NULL, obj) != NULL) {
                            return 0; 
                        }
                    }
                    return 1;
                }
            }
        } else if(abs(move_xy[0] - origin_xy[0]) > 1 || abs(move_xy[1] - origin_xy[1]) > 1) {
            return 0;
        } else {
            //If the square is threatened can't move
            if(square_attacked(move_xy, p_color, NULL, obj) == NULL) {
                return 1;
            } else if(square_attacked(move_xy, p_color, NULL, obj) != NULL){
                return 0;
            } else {
                return 0;
            }
        }
    }
}


int piece_pinned(int *origin_xy, char line, char p_color, piece (*obj)[8][8])
{
    int row, column, diff, real_diff, trace_x, trace_y, direction;
    int x_diff, y_diff, direction_x, direction_y;
    int king_xy[2];

    //If piece is the king then it can't be pinned
    if((*obj)[origin_xy[1]][origin_xy[0]].name == 'K' || (*obj)[origin_xy[1]][origin_xy[0]].name == 'k') {
        return 0;
    }
    //Searchs for the king position
    for(row = 0; row < 8; row++) {
        for(column = 0; column < 8; column++) {
            if(((*obj)[row][column].name == 'K' || (*obj)[row][column].name == 'k') && (*obj)[row][column].color ==  p_color) {
                king_xy[1] = row;
                king_xy[0] = column;
            }
        }
    }
    switch(line) {
        case 'h':
            //Piece can't be pinned if not in the same row
            if(king_xy[1] != origin_xy[1]) {
                return 0;
            }
            //Trace if any piece in between the king and the origin
            for(diff = abs(origin_xy[0] - king_xy[0]); diff > 1; diff--) {
                real_diff = (diff - 1) * ((king_xy[0] - origin_xy[0]) / abs(king_xy[0] - origin_xy[0]));
                if((*obj)[origin_xy[1]][origin_xy[0] + real_diff].name != ' ') {
                    return 0;
                }
            }
            //Direction relative to the king
            direction = ((king_xy[0] - origin_xy[0]) / abs(king_xy[0] - origin_xy[0]));
            //Trace if any piece in the opposite side of the piece
            for(trace_x = origin_xy[0] - direction; trace_x >= 0 && trace_x <= 7; trace_x = trace_x - direction) {
                //If another friendly piece is in between, the piece can't get pinned
                if((*obj)[origin_xy[1]][trace_x].name != ' ' && (*obj)[origin_xy[1]][trace_x].color == p_color) {
                    return 0;
                //If the piece is enemy check whether it can attack 
                } else if((*obj)[origin_xy[1]][trace_x].name != ' ') {
                    if((*obj)[origin_xy[1]][trace_x].name == 'R' || (*obj)[origin_xy[1]][trace_x].name == 'r' ) {
                        return 1;
                    } else if((*obj)[origin_xy[1]][trace_x].name == 'Q' || (*obj)[origin_xy[1]][trace_x].name == 'q') {
                        return 1;
                    } else {
                        return 0;
                    }
                }
            }
            break;
        case 'v':
            //Piece can't be pinned if not in the same column
            if(king_xy[0] != origin_xy[0]) {
                return 0;
            }
            for(diff = abs(origin_xy[1] - king_xy[1]); diff > 1; diff--) {
                real_diff = (diff - 1) * ((king_xy[1] - origin_xy[1]) / abs(king_xy[1] - origin_xy[1]));
                if((*obj)[origin_xy[1] + real_diff][origin_xy[0]].name != ' ') {
                    return 0;
                }
            }
            direction = ((king_xy[1] - origin_xy[1]) / abs(king_xy[1] - origin_xy[1]));
            for(trace_y = origin_xy[1] - direction; trace_y >= 0 && trace_y <= 7; trace_y = trace_y - direction) {
                if((*obj)[trace_y][origin_xy[0]].name != ' ' && (*obj)[trace_y][origin_xy[0]].color == p_color) {
                    return 0;
                } else if((*obj)[trace_y][origin_xy[0]].name != ' ') {
                    if((*obj)[trace_y][origin_xy[0]].name == 'R' || (*obj)[trace_y][origin_xy[0]].name == 'r' ) {
                        return 1;
                    } else if((*obj)[trace_y][origin_xy[0]].name == 'Q' || (*obj)[trace_y][origin_xy[0]].name == 'q') {
                        return 1;
                    } else {
                        return 0;
                    }
                }
            }
            break;
        case 'd':
            //Piece can't be pinned if not in the same diagonal
            if(abs(king_xy[0] - origin_xy[0]) != abs(king_xy[1] - origin_xy[1])) {
                return 0;
            }
            for(diff = abs(origin_xy[0] - king_xy[0]); diff > 1; diff--) {
                x_diff = (diff - 1) * ((king_xy[0] - origin_xy[0]) / abs(king_xy[0] - origin_xy[0]));
                y_diff = (diff - 1) * ((king_xy[1] - origin_xy[1]) / abs(king_xy[1] - origin_xy[1]));
                if((*obj)[origin_xy[1] + y_diff][origin_xy[0] + x_diff].name != ' ') {
                    return 0;
                }
            }
            direction_x = ((king_xy[0] - origin_xy[0]) / abs(king_xy[0] - origin_xy[0]));
            direction_y = ((king_xy[1] - origin_xy[1]) / abs(king_xy[1] - origin_xy[1]));
            trace_x = origin_xy[0] - direction_x;
            trace_y = origin_xy[1] - direction_y;
            while((trace_x >= 0 && trace_x <= 7) && (trace_y >= 0 && trace_y <= 7)) {
                if((*obj)[trace_y][trace_x].name != ' ' && (*obj)[trace_y][trace_x].color == p_color) {
                    return 0;
                } else if((*obj)[trace_y][trace_x].name != ' ' ) {
                    if((*obj)[trace_y][trace_x].name == 'B' || (*obj)[trace_y][trace_x].name == 'b' ) {
                        return 1;
                    } else if((*obj)[trace_y][trace_x].name == 'Q' || (*obj)[trace_y][trace_x].name == 'q' ) {
                        return 1;
                    } else {
                        return 0;
                    }
                }
                trace_x = trace_x - direction_x;
                trace_y = trace_y - direction_y;
            }
            break;
    }
    return 0;
}

int** square_attacked(int *origin_xy, char p_color, int** old_arr, piece (*obj)[8][8])
{
    int pawn_left, pawn_right;
    int row, column;
    int knight_attack, rook_attack, bishop_attack, queen_attack;
    int move_xy[2];
    char enemy_color, knight_symbol, bishop_symbol;
    char rook_symbol, queen_symbol, king_symbol;
    int** attackers;
    int* attack;
    int n_attacks, old_n_attacks;
    
    attackers = NULL;
    n_attacks = 0;

    if(old_arr != NULL) {
        old_n_attacks = (*(old_arr-1))[0];
        for(int p = 0; p < old_n_attacks; p++) {
            free(old_arr[p]);
        }
        free(old_arr-1);
    }

    //Check if attacked by pawn
    if(p_color == 'w') {
        pawn_left = (*obj)[origin_xy[1] + 1][origin_xy[0] - 1].name == 'p';
        pawn_right = (*obj)[origin_xy[1] + 1][origin_xy[0] + 1].name == 'p';
        if(origin_xy[0] == 0) {
            pawn_left = 0;
        }
        if(origin_xy[0] == 7) {
            pawn_right = 0;
        }
        if(pawn_left) {
            attack = malloc(2 * sizeof(int));
            attack[0] = origin_xy[0] - 1;
            attack[1] = origin_xy[1] +  1;
            attackers = realloc(attackers, (n_attacks + 2) * sizeof(int*));
            attackers[n_attacks + 1] = attack;
            n_attacks++;
        }
        if(pawn_right) {
            attack = malloc(2 * sizeof(int));
            attack[0] = origin_xy[0] + 1;
            attack[1] = origin_xy[1] +  1;
            attackers = realloc(attackers, (n_attacks + 2) * sizeof(int*));
            attackers[n_attacks + 1] = attack;
            n_attacks++;
        }
    } else {
        pawn_left = (*obj)[origin_xy[1] - 1][origin_xy[0] - 1].name == 'P';
        pawn_right = (*obj)[origin_xy[1] - 1][origin_xy[0] + 1].name == 'P';
        if(origin_xy[0] == 0) {
            pawn_left = 0;
        }
        if(origin_xy[0] == 7) {
            pawn_right = 0;
        }
        if(pawn_left) {
            attack = malloc(2 * sizeof(int));
            attack[0] = origin_xy[0] - 1;
            attack[1] = origin_xy[1] -  1;
            attackers = realloc(attackers, (n_attacks + 2) * sizeof(int*));
            attackers[n_attacks + 1] = attack;
            n_attacks++;
        }
        if(pawn_right) {
            attack = malloc(2 * sizeof(int));
            attack[0] = origin_xy[0] + 1;
            attack[1] = origin_xy[1] -  1;
            attackers = realloc(attackers, (n_attacks + 2) * sizeof(int*));
            attackers[n_attacks + 1] = attack;
            n_attacks++;
        }
 
    }
    //Sets the enemy piece depending on the color
    enemy_color = (p_color == 'w') ? 'b' : 'w';
    knight_symbol = (p_color == 'w') ? 'n' : 'N';
    bishop_symbol = (p_color == 'w') ? 'b' : 'B';
    rook_symbol = (p_color == 'w') ? 'r' : 'R';
    queen_symbol = (p_color == 'w') ? 'q' : 'Q';
    king_symbol = (p_color == 'w') ? 'k' : 'K';
    for(row = 0; row < 8; row++) {
        for(column = 0; column < 8; column++) {
            move_xy[1] = row;
            move_xy[0] = column;
            if((row == origin_xy[1]) && (column == origin_xy[0])) {
                continue;
            }
            if(p_color != (*obj)[origin_xy[1]][origin_xy[0]].color) {
                knight_attack = knight_move(move_xy, origin_xy, p_color, obj) && (*obj)[move_xy[1]][move_xy[0]].name == knight_symbol;
                bishop_attack = bishop_move(move_xy, origin_xy, p_color, obj) && (*obj)[move_xy[1]][move_xy[0]].name == bishop_symbol;
                rook_attack = rook_move(move_xy, origin_xy, p_color, obj) && (*obj)[move_xy[1]][move_xy[0]].name == rook_symbol;
                queen_attack = (bishop_move(move_xy, origin_xy, p_color, obj) || rook_move(move_xy, origin_xy, p_color, obj)) && (*obj)[move_xy[1]][move_xy[0]].name == queen_symbol;
            } else {
                knight_attack = knight_move(move_xy, origin_xy, enemy_color, obj) && (*obj)[move_xy[1]][move_xy[0]].name == knight_symbol;
                bishop_attack = bishop_move(move_xy, origin_xy, enemy_color, obj) && (*obj)[move_xy[1]][move_xy[0]].name == bishop_symbol;
                rook_attack = rook_move(move_xy, origin_xy, enemy_color, obj) && (*obj)[move_xy[1]][move_xy[0]].name == rook_symbol;
                queen_attack = (bishop_move(move_xy, origin_xy, enemy_color, obj) || rook_move(move_xy, origin_xy, enemy_color, obj)) && (*obj)[move_xy[1]][move_xy[0]].name == queen_symbol;
            }
            if(knight_attack || bishop_attack || rook_attack || queen_attack) {
                attack = malloc(2 * sizeof(int));
                attack[0] = column;
                attack[1] = row;
                attackers = realloc(attackers, (n_attacks + 2) * sizeof(int*));
                attackers[n_attacks + 1] = attack;
                n_attacks++;
            }
            if(!(abs(move_xy[0] - origin_xy[0]) > 1 || abs(move_xy[1] - origin_xy[1]) > 1) && (*obj)[move_xy[1]][move_xy[0]].name == king_symbol) {
                attack = malloc(2 * sizeof(int));
                attack[0] = column;
                attack[1] = row;
                attackers = realloc(attackers, (n_attacks + 2) * sizeof(int*));
                attackers[n_attacks + 1] = attack;
                n_attacks++;
            }
        }   
    }
    if(n_attacks > 0) {
        int* size = malloc(1 * sizeof(int));
        size[0] = n_attacks;
        attackers[0] = size;
        return (attackers+1);
    } else {
        return NULL;
    }
}

int** legal_moves(int* origin_xy, piece (*obj)[8][8], char p_color, int** attackers, int* castle, int* king, int** old_arr, piece blank)
{
    int row, column, n_moves, n_attacks, legal, old_n_moves;
    int h_pinned, v_pinned, d_pinned;
    int* move;
    int** moves;
    int move_xy[2];
    int** attack_d;
    int* xy_attack_d;
    int n_attacks_d, attack_i;
    int diagonal_ap, diagonal_ak;
    int diagonal_move_a, diagonal_move_k;
    char symbol_m, color_m;

    moves = NULL;
    n_moves = 0;

    if(old_arr != NULL) {
        old_n_moves = (*(old_arr-1))[0];
        for(int p = 0; p < old_n_moves; p++) {
            free(old_arr[p]);
        }
        free(old_arr-1);
    }


    if(attackers != NULL) {
        n_attacks = (*(attackers-1))[0];
    } else {
        n_attacks = 0;
    }

    char symbol = (*obj)[origin_xy[1]][origin_xy[0]].name;
    char color = (*obj)[origin_xy[1]][origin_xy[0]].color;

    if(!(color == p_color)) {
        return NULL;
    }
    
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
            } else if(symbol == 'Q' || symbol == 'q') {
                legal = (bishop_move(origin_xy, move_xy, p_color, obj) || rook_move(origin_xy, move_xy, p_color, obj));
            } else if(symbol == 'K' || symbol == 'k') {
                legal = king_move(origin_xy, move_xy, p_color, obj, castle);
            }

            if(legal == 0) {
                continue;
            }

            //Check if the move made lefts the king in check
            if(legal == 1) {
                symbol_m = (*obj)[move_xy[1]][move_xy[0]].name;
                if(symbol_m == ' ') {
                    color_m = ' ';
                } else {
                    color_m = (*obj)[move_xy[1]][move_xy[0]].color;
                }
                if((symbol == 'P' || symbol == 'p') && ((*obj)[move_xy[1]][move_xy[0]].name == ' ' && ((*obj)[move_xy[1]][move_xy[0]].enpassant == 1))) {
                    if(color == 'w') {
                        color_m = (*obj)[move_xy[1] - 1][move_xy[0]].color;
                        (*obj)[move_xy[1] - 1][move_xy[0]] = blank;
                        (*obj)[move_xy[1] - 1][move_xy[0]].name = ' ';
                    } else {
                        color_m = (*obj)[move_xy[1] + 1][move_xy[0]].color;
                        (*obj)[move_xy[1] + 1][move_xy[0]] = blank;
                        (*obj)[move_xy[1] + 1][move_xy[0]].name = ' ';
                    }
                }
                (*obj)[move_xy[1]][move_xy[0]].name = symbol;
                (*obj)[move_xy[1]][move_xy[0]].color = color;
                (*obj)[origin_xy[1]][origin_xy[0]] = blank;
                (*obj)[origin_xy[1]][origin_xy[0]].name = ' ';
                if((symbol == 'K') || (symbol == 'k')) {
                    if(square_attacked(move_xy, color, NULL, obj) != NULL) {
                        legal = 0;
                    }
                } else {
                    if(square_attacked(king, color, NULL, obj) != NULL) {
                        legal = 0;
                    }   
                }
                undo_move(origin_xy, move_xy, obj, blank, symbol_m, color_m);
                if(legal == 0) {
                    continue;
                }
            }

            //Checks if any the piece is pinned in any axis
            h_pinned = piece_pinned(origin_xy, 'h', p_color, obj);
            v_pinned = piece_pinned(origin_xy, 'v', p_color, obj);
            d_pinned = piece_pinned(origin_xy, 'd', p_color, obj);

            if(h_pinned && move_xy[1] != origin_xy[1]) {
                legal = 0;
            } else if(v_pinned && move_xy[0] != origin_xy[0]) {
                legal = 0;
            } else if(d_pinned) {
                attack_d = square_attacked(origin_xy, p_color, NULL, obj);
                xy_attack_d = NULL;
                n_attacks_d = (*(attack_d-1))[0];
                for(attack_i = 0; attack_i < n_attacks_d; attack_i++) {
                    xy_attack_d = attack_d[attack_i];
                    diagonal_ap = abs(xy_attack_d[0] - origin_xy[0]) == abs(xy_attack_d[1] - origin_xy[1]);
                    diagonal_ak = abs(xy_attack_d[0] - king[0]) == abs(xy_attack_d[1] - king[1]);
                    diagonal_move_a = abs(move_xy[0] - xy_attack_d[0]) == abs(move_xy[1] - xy_attack_d[1]);
                    diagonal_move_k = abs(move_xy[0] - king[0]) == abs(move_xy[1] - king[1]);
                    if(diagonal_ak && diagonal_ap && diagonal_move_a && diagonal_move_k && legal) {
                        legal = 1;
                        free(attack_d[attack_i]);
                        break;
                    } else {
                        legal = 0;
                        free(attack_d[attack_i]);
                    }
                }
                free(attack_d-1);
            }

            if(n_attacks > 1 && !(symbol == 'K' || symbol == 'k')) {
                legal = 0;
            } else if(n_attacks == 1) {
                int* attack_arr = attackers[0];
                char attack_symbol = (*obj)[attack_arr[1]][attack_arr[0]].name;
                if(!(symbol == 'K' || symbol == 'k')) {
                    if(legal == 1 && (move_xy[0] == attack_arr[0] && move_xy[1] == attack_arr[1])) {
                        legal = 1;
                    } else if(legal == 1) {
                        if(attack_symbol == 'N' || attack_symbol == 'n') {
                            legal = 0;
                        } else if(attack_symbol == 'P' || attack_symbol == 'p') {
                            legal = 0;
                        } else if(attack_symbol == 'R' || attack_symbol == 'r') {
                            //Atttack vertically
                            if(attack_arr[0] == king[0]) {
                                if(king[1] < attack_arr[1]) {
                                    if((move_xy[0] == king[0]) && (move_xy[1] > king[1] && move_xy[1] < attack_arr[1])) {
                                        legal = 1;
                                    } else {
                                        legal = 0;
                                    }
                                } else {
                                    if((move_xy[0] == king[0]) && (move_xy[1] < king[1] && move_xy[1] > attack_arr[1])) {
                                        legal = 1;
                                    } else {
                                        legal = 0;
                                    }
                                }
                            //Atttack horizontally
                            } else {
                                if(king[0] < attack_arr[0]) {
                                    if((move_xy[1] == king[1]) && (move_xy[0] > king[0] && move_xy[0] < attack_arr[0])) {
                                        legal = 1;
                                    } else {
                                        legal = 0;
                                    }
                                } else {
                                    if((move_xy[1] == king[1]) && (move_xy[0] < king[0] && move_xy[0] > attack_arr[0])) {
                                        legal = 1;
                                    } else {
                                        legal = 0;
                                    }
                                }
                            }
                        } else if(attack_symbol == 'B' || attack_symbol == 'b') {
                            if(abs(king[0] - move_xy[0]) == abs(king[1] - move_xy[1])) {
                                if((attack_arr[0] - move_xy[0]) == 0) {
                                    legal = 0;
                                    continue;
                                }
                                int direction_x_move = (attack_arr[0] - move_xy[0]) / abs(attack_arr[0] - move_xy[0]);
                                int direction_x_king = (attack_arr[0] - king[0]) / abs(attack_arr[0] - king[0]);
                                if((attack_arr[1] - move_xy[1]) == 0) {
                                    legal = 0;
                                    continue;
                                }
                                int direction_y_move = (attack_arr[1] - move_xy[1]) / abs(attack_arr[1] - move_xy[1]);
                                int direction_y_king = (attack_arr[1] - king[1]) / abs(attack_arr[1] - king[1]);
                                if((direction_x_king == direction_x_move) && (direction_y_king == direction_y_move)) {
                                    if(abs(attack_arr[1] - move_xy[1]) == abs(attack_arr[0] - move_xy[0])) {
                                        legal = 1;
                                    } else {
                                        legal = 0;
                                    }
                                } else {
                                    legal = 0;
                                }
                            } else {
                                legal = 0;
                            }
                        } else if(attack_symbol == 'Q' || attack_symbol == 'q') {
                            if(attack_arr[0] == king[0]) {
                                if(king[1] < attack_arr[1]) {
                                    if((move_xy[0] == king[0]) && (move_xy[1] > king[1] && move_xy[1] < attack_arr[1])) {
                                        legal = 1;
                                    } else {
                                        legal = 0;
                                    }
                                } else {
                                    if((move_xy[0] == king[0]) && (move_xy[1] < king[1] && move_xy[1] > attack_arr[1])) {
                                        legal = 1;
                                    } else {
                                        legal = 0;
                                    }
                                }
                            } else if(attack_arr[1] == king[1]) {
                                if(king[0] < attack_arr[0]) {
                                    if((move_xy[1] == king[1]) && (move_xy[0] > king[0] && move_xy[0] < attack_arr[0])) {
                                        legal = 1;
                                    } else {
                                        legal = 0;
                                    }
                                } else {
                                    if((move_xy[1] == king[1]) && (move_xy[0] < king[0] && move_xy[0] > attack_arr[0])) {
                                        legal = 1;
                                    } else {
                                        legal = 0;
                                    }
                                }
                            } else {
                                if(abs(king[0] - move_xy[0]) == abs(king[1] - move_xy[1])) {
                                    if((attack_arr[0] - move_xy[0]) == 0) {
                                        legal = 0;
                                        continue;
                                    }
                                    int direction_x_move = (attack_arr[0] - move_xy[0]) / abs(attack_arr[0] - move_xy[0]);
                                    int direction_x_king = (attack_arr[0] - king[0]) / abs(attack_arr[0] - king[0]);
                                    if((attack_arr[1] - move_xy[1]) == 0) {
                                        legal = 0;
                                        continue;
                                    }
                                    int direction_y_move = (attack_arr[1] - move_xy[1]) / abs(attack_arr[1] - move_xy[1]);
                                    int direction_y_king = (attack_arr[1] - king[1]) / abs(attack_arr[1] - king[1]);
                                    if(direction_x_king == direction_x_move && direction_y_king == direction_y_move) {
                                        if(abs(attack_arr[1] - move_xy[1]) == abs(attack_arr[0] - move_xy[0])) {
                                            legal = 1;
                                        } else {
                                            legal = 0;
                                        }
                                    } else {
                                        legal = 0;
                                    }
                                } else {
                                    legal = 0;
                                }
                            } 
                        }
                    } else {
                        legal = 0;
                    }
                }
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
    if(n_moves > 0) {
        int* size = malloc(1 * sizeof(int));
        size[0] = n_moves;
        moves[0] = size;
        return (moves+1);
    } else {
        return NULL;
    }
}
