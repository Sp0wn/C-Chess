#include "engine.h"

#include "../Game/piece.h"

#include "../Game/rules.h"
#include "../UI/Board.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void play_random(piece (*obj)[8][8], char player, int* king, int* castle, piece blank)
{
    int row, column, n_moves, moves_index, option;
    int row_i, col_i;
    int origin_xy[2];
    int **king_attack, **moves;
    int *arr_r, *arr_c;

    char symbol;

    king_attack = moves = NULL;

    //Init seed
    srand(time(NULL));

    //Init arrays
    row_i = col_i = 8;
    arr_r = fill_arr(NULL, row_i, -1);
    arr_c = fill_arr(NULL, col_i, -1);
    row = rand() % 8;
    column = rand() % 8;
   
    //Loop to find a piece with legal moves
    do {
        //Get a random square
        origin_xy[0] = arr_c[column];
        origin_xy[1] = arr_r[row];

        //Check for the entire row
        while(1) {
            //Check if there is a friendly piece in the square
            if((*obj)[origin_xy[1]][origin_xy[0]].color == player) {
                king_attack = square_attacked(king, player, king_attack, obj);
                moves = legal_moves(origin_xy, obj, player, king_attack, castle, king, moves, blank);
                //Check if it has moves aviable
                if(moves != NULL) {
                    break;
                }
            }
            //Break loop if column array is empty
            if(col_i == 1) {
                break;
            }
            //Start deleting used numbers
            col_i = col_i - 1;
            arr_c = fill_arr(arr_c, col_i, origin_xy[0]);
            column = rand() % col_i;
            origin_xy[0] = arr_c[column];
        }
        //Reset column array
        free(arr_c);
        col_i = 8;
        arr_c = fill_arr(NULL, col_i, -1);
        column = rand() % 8;

        //Check if it has moves available
        if(moves != NULL) {
            free(arr_c);
            free(arr_r);
            break;
        }

        row_i = row_i - 1;
        arr_r = fill_arr(arr_r, row_i, origin_xy[1]);
        row = rand() % row_i;
        origin_xy[1] = arr_r[row];

    } while(1);

    //Get number of aviable moves
    //and randomly select one move
    n_moves = (*(moves-1))[0];
    moves_index = rand() % n_moves;

    //Play the select move
    make_move(moves[moves_index], origin_xy, moves, obj, blank, castle, king);

    //Make promotion
    symbol = (*obj)[moves[moves_index][1]][moves[moves_index][0]].name;
    if((symbol == 'P' || symbol == 'p') && (moves[moves_index][1] == 0 || moves[moves_index][1] == 7)) {
        option = (rand() % 4) + 1;
        make_promotion(option, moves[moves_index], obj, player);
    }
}

int* fill_arr(int* old_arr, int size, int excluded)
{
    //Init space for new array
    int* new_arr = malloc(sizeof(int) * size);

    //Init index of old array
    int old_i = 0;

    //If there isn't an old array create a new one
    if(old_arr == NULL) {
        for(int i = 0; i < 8; i++) {
            new_arr[i] = i;
        }
        return new_arr;
    } 

    //Loop through the entire set
    for(int i = 0; i < 8; i++) {
        //Stop the loop when the limit is reached
        if(old_i - 1 == size) {
            break;
        }
        //Copy the numbers of the old array
        if(old_arr[old_i] == i) {
            if(i < excluded) {
                new_arr[old_i] = i;
            } else if(i == excluded) {
                old_i = old_i + 1;
                continue;
            } else if(i > excluded) {
                new_arr[old_i - 1] = i;
            }
            old_i = old_i + 1;
        }
    }
    free(old_arr);
    return new_arr;
}
