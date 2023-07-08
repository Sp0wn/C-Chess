#include "engine.h"

#include "../Game/piece.h"

#include "../Game/rules.h"
#include "../UI/Board.h"

#include "eval.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>

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

float minimax(piece (*obj)[8][8], int* depth, int is_max, float alpha, float beta, piece blank, int* castle_w, int* castle_b, char color)
{
    //TODO: Implement promotion in the simulation
    int **attack_s, **moves;
    int *enpassant_xy;
    int origin_xy[2], move_xy[2], king_xy[2], original_castle[2];
    int winner, perspective, material;
    int row, col;
    int n_moves, moves_i;
    int pm, pa, n_attacks;
    char new_color, old_p, old_c;
    float value, new_value;
    float tie_bias;

    attack_s = moves = NULL;

    //Searchs for king position
    for(row = 0; row < 8; row++) {
        for(col = 0; col < 8; col++) {
            if(((*obj)[row][col].name == 'K' || (*obj)[row][col].name == 'k') && (*obj)[row][col].color ==  color) {
                king_xy[1] = row;
                king_xy[0] = col;
            }
        }
    }

    /*for(row = 0; row < 8; row++) {
        for(col = 0; col < 8; col++) {
            printf("%c ", (*obj)[row][col].name);
        }
        printf("\n");
    }
    printf("to play: %c ;depth of: %i\n\n", color, depth[0]);*/

    //Bias used in order to prevent
    //unwanted stalemate
    tie_bias = -0.01;

    //Check if game has ended
    if(color == 'w') {
        winner = check_checkmate(obj, color, blank, castle_w);
    } else {
        winner = check_checkmate(obj, color, blank, castle_b);
    }
    perspective = (is_max == 1) ? 1 : -1;
    if(winner != -1) {
        if(winner == 0) {
            //A tie is considered as
            //a 0, while when material
            //is even there will be a bias
            return 0;
        } else {
            //Range {+-50, +-100} as max depth is 50
            //The bigger the delta of the depth is
            //the less value will have for any player
            return (perspective * -100.0) + (perspective * (depth[1] - depth[0]));
        }
    }
    //Check the value of the sum
    //of all the pieces
    if(depth[0] == 0) {
        material = eval_material(obj, color);
        if(material == 0) {
            return tie_bias * perspective;
        } else {
            return material * perspective;
        }
    }

    //Maximixing player
    if(is_max == 1) {
        value = -1000.0;
        //Searchs through the whole board
        for(row = 0; row < 8; row++) {
            for(col = 0; col < 8; col++) {
                //Checks if the piece is friendly
                if((*obj)[row][col].color == color) {
                    origin_xy[0] = col;
                    origin_xy[1] = row;
                    //Checks if the selected piece can be moved
                    /*if(((*obj)[1][5].name == 'P') && ((*obj)[1][5].color == 'b')) {
                        printf("Really!1\n");
                        printf("Color a: %c\n", color);
                        printf("X1:%i, Y1:%i; X2:, Y2: ;val = , depth = %i\n", origin_xy[0], origin_xy[1],  depth[0]);
                        sleep(5);
                        exit(0);
                    }*/     
                    attack_s = square_attacked(king_xy, color, attack_s, obj);
                    if(color == 'w') {
                        moves = legal_moves(origin_xy, obj, color, attack_s, castle_w, king_xy, moves, blank);
                    } else {
                        moves = legal_moves(origin_xy, obj, color, attack_s, castle_b, king_xy, moves, blank);
                    }
                    /*if(((*obj)[1][5].name == 'P') && ((*obj)[1][5].color == 'b')) {
                        printf("Really!2\n");
                        printf("Color a: %c\n", color);
                        printf("X1:%i, Y1:%i; X2:, Y2: ;val = , depth = %i\n", origin_xy[0], origin_xy[1],  depth[0]);
                        sleep(5);
                        exit(0);
                    }*/     
                    if(moves != NULL) {
                        n_moves = (*(moves-1))[0];
                        //Loops through the legal moves
                        for(moves_i = 0; moves_i < n_moves; moves_i++) {
                            //Save values that will be modified
                            if(color == 'w') {
                                original_castle[0] = castle_w[0];
                                original_castle[1] = castle_w[1];
                            } else {
                                original_castle[0] = castle_b[0];
                                original_castle[1] = castle_b[1];
                            }
                            enpassant_xy = search_enpassant(obj);
                            old_p = (*obj)[moves[moves_i][1]][moves[moves_i][0]].name;
                            old_c = (*obj)[moves[moves_i][1]][moves[moves_i][0]].color;
                            /*if((*obj)[origin_xy[1]][origin_xy[0]].name == 'P') {
                                if((moves[moves_i][0] == 4) && (moves[moves_i][1] == 0)) {
                                    printf("Color a: %c\n", color);
                                    sleep(2);
                                }
                            }*/
                            //Make the move and modify values to pass recursively
                            if(color == 'w') {
                                make_move(moves[moves_i], origin_xy, moves, obj, blank, castle_w, king_xy);
                            } else {
                                make_move(moves[moves_i], origin_xy, moves, obj, blank, castle_b, king_xy);
                            }
                            depth[0] = depth[0] - 1;
                            if(((*obj)[moves[moves_i][1]][moves[moves_i][0]].name == 'P') && (moves[moves_i][1] == 7)) {
                                for(int option = 1; option < 5; option++) {
                                    //exit(0);
                                    make_promotion(option, moves[moves_i], obj, color);
                                    new_color = (color == 'w') ? 'b' : 'w';
                                    new_value = minimax(obj, depth, 0, alpha, beta, blank, castle_w, castle_b, new_color);
                                    value = fmaxf(value, new_value);
                                    alpha = fmaxf(alpha, value);
                                    undo_promotion(obj, color, moves[moves_i]);
                                    if(beta <= alpha) {
                                        break;
                                    } 
                                }
                            } else if(((*obj)[moves[moves_i][1]][moves[moves_i][0]].name == 'p') && (moves[moves_i][1] == 0)) {
                                for(int option = 1; option < 5; option++) {
                                    //exit(0);
                                    make_promotion(option, moves[moves_i], obj, color);
                                    new_color = (color == 'w') ? 'b' : 'w';
                                    new_value = minimax(obj, depth, 0, alpha, beta, blank, castle_w, castle_b, new_color);
                                    value = fmaxf(value, new_value);
                                    alpha = fmaxf(alpha, value);
                                    undo_promotion(obj, color, moves[moves_i]);
                                    if(beta <= alpha) {
                                        break;
                                    } 
                                }
                            } else {
                                new_color = (color == 'w') ? 'b' : 'w';
                                new_value = minimax(obj, depth, 0, alpha, beta, blank, castle_w, castle_b, new_color);
                                value = fmaxf(value, new_value);
                                alpha = fmaxf(alpha, value);
                            }
                            //After ending the recursion undo the move and reset the values
                            if(color == 'w') {
                                undo_move(origin_xy, moves[moves_i], obj, blank, castle_w, original_castle, king_xy, enpassant_xy, old_p, old_c);
                            } else {
                                undo_move(origin_xy, moves[moves_i], obj, blank, castle_b, original_castle, king_xy, enpassant_xy, old_p, old_c);
                            }
                            /*if(((*obj)[1][5].name == 'P') && ((*obj)[1][5].color == 'b')) {
                                printf("Really! %i\n", is_max);
                                printf("Color a: %c\n", color);
                                printf("X1:%i, Y1:%i; X2:%i, Y2:%i ;val = %f, depth = %i\n", origin_xy[0], origin_xy[1], moves[moves_i][0], moves[moves_i][1], new_value, depth[0]);
                                sleep(5);
                                exit(0);
                            }*/     
                            if(enpassant_xy != NULL) {
                                free(enpassant_xy);
                            }
                            depth[0] = depth[0] + 1;
                            //printf("X1:%i, Y1:%i; X2:%i, Y2:%i ;val = %f, depth = %i\n", origin_xy[0], origin_xy[1], moves[moves_i][0], moves[moves_i][1], new_value, depth[0]);
                            if(beta <= alpha) {
                                break;
                            }
                        }
                    }
                }
                if(beta <= alpha) {
                    break;
                }
            }
            if(beta <= alpha) {
                break;
            }
        }
    //Minimizing player
    } else {
        value = 1000;
        for(row = 0; row < 8; row++) {
            for(col = 0; col < 8; col++) {
                if((*obj)[row][col].color == color) {
                    origin_xy[0] = col;
                    origin_xy[1] = row;
                    /*if(((*obj)[1][5].name == 'P') && ((*obj)[1][5].color == 'b')) {
                        printf("Really!1\n");
                        printf("Color a: %c\n", color);
                        printf("X1:%i, Y1:%i; X2:, Y2: ;val = , depth = %i\n", origin_xy[0], origin_xy[1],  depth[0]);
                        sleep(5);
                        exit(0);
                    }*/
                    attack_s = square_attacked(king_xy, color, attack_s, obj);
                    if(color == 'w') {
                        moves = legal_moves(origin_xy, obj, color, attack_s, castle_w, king_xy, moves, blank);
                    } else {
                        moves = legal_moves(origin_xy, obj, color, attack_s, castle_b, king_xy, moves, blank);
                    }
                    /*if(((*obj)[1][5].name == 'P') && ((*obj)[1][5].color == 'b')) {
                        printf("Really2!\n");
                        printf("Color a: %c\n", color);
                        printf("X1:%i, Y1:%i; X2:, Y2: ;val = , depth = %i\n", origin_xy[0], origin_xy[1],  depth[0]);
                        sleep(5);
                        exit(0);
                    }*/
                    if(moves != NULL) {
                        n_moves = (*(moves-1))[0];
                        for(moves_i = 0; moves_i < n_moves; moves_i++) {
                            if(color == 'w') {
                                original_castle[0] = castle_w[0];
                                original_castle[1] = castle_w[1];
                            } else {
                                original_castle[0] = castle_b[0];
                                original_castle[1] = castle_b[1];
                            }
                            enpassant_xy = search_enpassant(obj);
                            old_p = (*obj)[moves[moves_i][1]][moves[moves_i][0]].name;
                            old_c = (*obj)[moves[moves_i][1]][moves[moves_i][0]].color;
                            /*if((*obj)[origin_xy[1]][origin_xy[0]].name == 'P') {
                                if((moves[moves_i][0] == 4) && (moves[moves_i][1] == 0)) {
                                    printf("Color a: %c\n", color);
                                    sleep(2);
                                }
                            }*/
                            if(color == 'w') {
                                make_move(moves[moves_i], origin_xy, moves, obj, blank, castle_w, king_xy);
                            } else {
                                make_move(moves[moves_i], origin_xy, moves, obj, blank, castle_b, king_xy);
                            }
                            depth[0] = depth[0] - 1;
                            if(((*obj)[moves[moves_i][1]][moves[moves_i][0]].name == 'P') && (moves[moves_i][1] == 7)) {
                                for(int option = 1; option < 5; option++) {
                                    //exit(0);
                                    make_promotion(option, moves[moves_i], obj, color);
                                    new_color = (color == 'w') ? 'b' : 'w';
                                    new_value = minimax(obj, depth, 1, alpha, beta, blank, castle_w, castle_b, new_color);
                                    value = fminf(value, new_value);
                                    beta = fminf(beta, value);
                                    undo_promotion(obj, color, moves[moves_i]);
                                    //if(beta <= alpha) {
                                    //    break;
                                    //} 
                                }
                            } else if(((*obj)[moves[moves_i][1]][moves[moves_i][0]].name == 'p') && (moves[moves_i][1] == 0)) {
                                for(int option = 1; option < 5; option++) {
                                    //exit(0);
                                    make_promotion(option, moves[moves_i], obj, color);
                                    new_color = (color == 'w') ? 'b' : 'w';
                                    new_value = minimax(obj, depth, 1, alpha, beta, blank, castle_w, castle_b, new_color);
                                    value = fminf(value, new_value);
                                    beta = fminf(beta, value);
                                    undo_promotion(obj, color, moves[moves_i]);
                                    //if(beta <= alpha) {
                                    //    break;
                                    //} 
                                }
                            } else {
                                new_color = (color == 'w') ? 'b' : 'w';
                                new_value = minimax(obj, depth, 1, alpha, beta, blank, castle_w, castle_b, new_color);
                                value = fminf(value, new_value);
                                beta = fminf(beta, value);
                            }
                            if(color == 'w') {
                                undo_move(origin_xy, moves[moves_i], obj, blank, castle_w, original_castle, king_xy, enpassant_xy, old_p, old_c);
                            } else {
                                undo_move(origin_xy, moves[moves_i], obj, blank, castle_b, original_castle, king_xy, enpassant_xy, old_p, old_c);
                            }
                            /*if(((*obj)[1][5].name == 'P') && ((*obj)[1][5].color == 'b')) {
                                printf("Really! %i\n", is_max);
                                printf("Color a: %c\n", color);
                                printf("X1:%i, Y1:%i; X2:%i, Y2:%i ;val = %f, depth = %i\n", origin_xy[0], origin_xy[1], moves[moves_i][0], moves[moves_i][1], new_value, depth[0]);
                                sleep(5);
                                exit(0);
                            }*/ 
                            if(enpassant_xy != NULL) {
                                free(enpassant_xy);
                            }
                            depth[0] = depth[0] + 1;
                            //printf("X1:%i, Y1:%i; X2:%i, Y2:%i ;val = %f, depth = %i\n", origin_xy[0], origin_xy[1], moves[moves_i][0], moves[moves_i][1], new_value, depth[0]);
                            if(beta <= alpha) {
                                break;
                            }
                        }
                    }
                }
                if(beta <= alpha) {
                    break;
                }
            }
            if(beta <= alpha) {
                break;
            }
        }
    }

    //Clean left memory
    if(attack_s != NULL) {
        n_attacks = (*(attack_s-1))[0];
        for(pa = 0; pa < n_attacks; pa++) {
            free(attack_s[pa]);
        }
        free(attack_s-1);
    }
    if(moves != NULL) {
        n_moves = (*(moves-1))[0];
        for(pm = 0; pm < n_moves; pm++) {
            free(moves[pm]);
        }
        free(moves-1);
    }
 
    return value;
}

void play_engine(piece (*obj)[8][8], char player, int *king, int *castle_w, int* castle_b, piece blank, int* depth)
{
    float value = -1000.0;
    int row, col;
    int origin_xy[2], original_castle[2];
    int n_moves, moves_i;
    char old_p, old_c;
    char new_color;
    float new_value;
    int best_move[2], best_origin[2];
    int best_promotion;
    int n_attacks, pa, pm;
    int* enpassant_xy;
    int **attack_s, **moves;

    attack_s = moves = NULL;
    for(row = 0; row < 8; row++) {
        for(col = 0; col < 8; col++) {
            if((*obj)[row][col].color == player) {
                origin_xy[0] = col;
                origin_xy[1] = row;
                attack_s = square_attacked(king, player, attack_s, obj);
                if(player == 'w') {
                    moves = legal_moves(origin_xy, obj, player, attack_s, castle_w, king, moves, blank);
                } else {
                    moves = legal_moves(origin_xy, obj, player, attack_s, castle_b, king, moves, blank);
                }
                if(moves != NULL) {
                    n_moves = (*(moves-1))[0];
                    for(moves_i = 0; moves_i < n_moves; moves_i++) {
                        if(player == 'w') {
                            original_castle[0] = castle_w[0];
                            original_castle[1] = castle_w[1];
                        } else {
                            original_castle[0] = castle_b[0];
                            original_castle[1] = castle_b[1];
                        }
                        enpassant_xy = search_enpassant(obj);
                        old_p = (*obj)[moves[moves_i][1]][moves[moves_i][0]].name;
                        old_c = (*obj)[moves[moves_i][1]][moves[moves_i][0]].color;
                        if(player == 'w') {
                            make_move(moves[moves_i], origin_xy, moves, obj, blank, castle_w, king);
                        } else {
                            make_move(moves[moves_i], origin_xy, moves, obj, blank, castle_b, king);
                        }
                        if(((*obj)[moves[moves_i][1]][moves[moves_i][0]].name == 'P') && (moves[moves_i][1] == 7)) {
                            for(int option = 1; option < 5; option++) {
                                make_promotion(option, moves[moves_i], obj, player);
                                new_color = (player == 'w') ? 'b' : 'w';
                                new_value = minimax(obj, depth, 0, -1000.0, 1000.0, blank, castle_w, castle_b, new_color);
                                undo_promotion(obj, player, moves[moves_i]);
                                if(new_value > value) {
                                    best_origin[0] = col;
                                    best_origin[1] = row;
                                    best_move[0] = moves[moves_i][0];
                                    best_move[1] = moves[moves_i][1];
                                    best_promotion = option;
                                }
                                value = fmaxf(value, new_value);
                            }
                        } else if(((*obj)[moves[moves_i][1]][moves[moves_i][0]].name == 'p') && (moves[moves_i][1] == 0)) {
                            for(int option = 1; option < 5; option++) {
                                make_promotion(option, moves[moves_i], obj, player);
                                new_color = (player == 'w') ? 'b' : 'w';
                                new_value = minimax(obj, depth, 0, -1000.0, 1000.0, blank, castle_w, castle_b, new_color);
                                undo_promotion(obj, player, moves[moves_i]);
                                if(new_value > value) {
                                    best_origin[0] = col;
                                    best_origin[1] = row;
                                    best_move[0] = moves[moves_i][0];
                                    best_move[1] = moves[moves_i][1];
                                    best_promotion = option;
                                }
                                value = fmaxf(value, new_value);
                            }
                        } else {
                            new_color = (player == 'w') ? 'b' : 'w';
                            new_value = minimax(obj, depth, 0, -1000.0, 1000.0, blank, castle_w, castle_b, new_color);
                            if(new_value > value) {
                                best_origin[0] = col;
                                best_origin[1] = row;
                                best_move[0] = moves[moves_i][0];
                                best_move[1] = moves[moves_i][1];
                            }
                            value = fmaxf(value, new_value);
                        }
                        if(player == 'w') {
                            undo_move(origin_xy, moves[moves_i], obj, blank, castle_w, original_castle, king, enpassant_xy, old_p, old_c);
                        } else {
                            undo_move(origin_xy, moves[moves_i], obj, blank, castle_b, original_castle, king, enpassant_xy, old_p, old_c);
                        }
                        if(enpassant_xy != NULL) {
                            free(enpassant_xy);
                        }
                    }
                }
            }
        }
    }
    int** moves_temp = malloc(2 * sizeof(int*));
    int size_temp = 1;
    int* p_size = &size_temp;
    moves_temp[0] = p_size;
    moves_temp[1] = best_move;

    if(player == 'w') {
        make_move(best_move, best_origin, moves_temp + 1, obj, blank, castle_w, king);
    } else {
        make_move(best_move, best_origin, moves_temp + 1, obj, blank, castle_b, king);
    }
    char symbol = (*obj)[best_move[1]][best_move[0]].name;
    if((symbol == 'P' || symbol == 'p') && (best_move[1] == 0 || best_move[1] == 7)) {
        make_promotion(best_promotion, best_move, obj, player);
    }

    free(moves_temp);
    if(attack_s != NULL) {
        n_attacks = (*(attack_s-1))[0];
        for(pa = 0; pa < n_attacks; pa++) {
            free(attack_s[pa]);
        }
        free(attack_s-1);
    }
    if(moves != NULL) {
        n_moves = (*(moves-1))[0];
        for(pm = 0; pm < n_moves; pm++) {
            free(moves[pm]);
        }
        free(moves-1);
    }
}
