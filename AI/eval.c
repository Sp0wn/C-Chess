#include "eval.h"

#include <stdlib.h>

#include "../Game/piece.h"
#include "../Game/rules.h"

const double wpawn_table[8][8] = {
    {0,0,0,0,0,0,0,0},
    {0.5,0,0,-0.5,-0.5,0,0,0.5},
    {0,0,0,0.5,0.5,0,0,0},
    {-0.2,0,0,1,1,0,0,-0.2},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0}
};

const double bpawn_table[8][8] = {
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {-0.2,0,0,1,1,0,0,-0.2},
    {0,0,0,0.5,0.5,0,0,0},
    {0.5,0,0,-0.5,-0.5,0,0,0.5},
    {0,0,0,0,0,0,0,0}
};

float eval_material(piece (*obj)[8][8], char color)
{
    int row, col;
    char symbol;

    float eval = 0;

    for(row = 0; row < 8; row++) {
        for(col = 0; col < 8; col++) {
            symbol = (*obj)[row][col].name;
            if((*obj)[row][col].color == 'w') {
                switch(symbol) {
                    case 'P':
                        eval = eval + 1;
                        eval = eval + wpawn_table[row][col];
                        break;
                    case 'N':
                        eval = eval + 3;
                        break;
                    case 'B':
                        eval = eval + 3;
                        break;
                    case 'R':
                        eval = eval + 5;
                        break;
                    case 'Q':
                        eval = eval + 9;
                        break;
                }
            } else if((*obj)[row][col].color == 'b') {
                switch(symbol) {
                    case 'p':
                        eval = eval - 1;
                        eval = eval - bpawn_table[row][col];
                        break;
                    case 'n':
                        eval = eval - 3;
                        break;
                    case 'b':
                        eval = eval - 3;
                        break;
                    case 'r':
                        eval = eval - 5;
                        break;
                    case 'q':
                        eval = eval - 9;
                        break;
                }
            } else {
                continue;
            }
        }
    }

    int perspective = (color == 'w') ? 1 : -1;
    return eval * perspective;
}

float has_doublepawns(piece (*obj)[8][8], char color)
{
    float eval = 0;
    int row, col; 
    float n_wpawns, n_bpawns;

    for(row = 0; row < 8; row++) {
        n_wpawns = 0;
        n_bpawns = 0;
        for(col = 0; col < 8; col++) {
            if((*obj)[row][col].name == 'P') {
                n_wpawns = n_wpawns + 1;
            } else if((*obj)[row][col].name == 'p') {
                n_bpawns = n_bpawns + 1;
            }  
        }
        if(n_wpawns > 1) {
            eval = eval - (n_wpawns / 10);
        }
        if(n_bpawns > 1) {
            eval = eval + (n_bpawns / 10);
        }
    }

    int perspective = (color == 'w') ? 1 : -1;
    return eval * perspective;
}

int check_checkmate(piece (*obj)[8][8], char color, piece blank, int* castle)
{
    int row, col, checkmate;
    int **attack_k, **moves;
    int king_xy[2], xy_temp[2];

    //Searchs for king position
    for(row = 0; row < 8; row++) {
        for(col = 0; col < 8; col++) {
            if(((*obj)[row][col].name == 'K' || (*obj)[row][col].name == 'k') && (*obj)[row][col].color ==  color) {
                king_xy[1] = row;
                king_xy[0] = col;
            }
        }
    }
 
    attack_k = NULL;
    moves = NULL;

    //Check if king is attacked
    attack_k = square_attacked(king_xy, color, NULL, obj);

    //Search for any available move
    for(row = 0;row < 8; row++) {
        for(col = 0; col < 8; col++) {
            xy_temp[0] = col;
            xy_temp[1] = row;
            if((*obj)[row][col].color == color && ((*obj)[row][col].name == 'K') || (*obj)[row][col].name == 'k') {
                moves = legal_moves(xy_temp, obj, color, attack_k, castle, king_xy, moves, blank);
            } else if((*obj)[row][col].color == color) {
                moves = legal_moves(xy_temp, obj, color, attack_k, castle, king_xy, moves, blank);
            } else {
                continue;
            }
            if((moves != NULL)) {
                break;
            }
        }
        if((moves != NULL)) {
            break;
        }
    }
 
    //Checkmate
    if((attack_k != NULL) && (moves == NULL)) {
        checkmate = 1;
    //Stalemate
    } else if((attack_k == NULL) && (moves == NULL)) {
        checkmate = 0;
    //Nothing
    } else {
        checkmate = -1;
    }

    if(attack_k != NULL) {
        int pa, n_attacks;
        n_attacks = (*(attack_k-1))[0];
        for(pa = 0; pa < n_attacks; pa++) {
            free(attack_k[pa]);
        }
        free(attack_k-1);
    }
    if(moves != NULL) {
        int pm, n_moves;
        n_moves = (*(moves-1))[0];
        for(pm = 0; pm < n_moves; pm++) {
            free(moves[pm]);
        }
        free(moves-1);
    }
 
    return checkmate;
}

