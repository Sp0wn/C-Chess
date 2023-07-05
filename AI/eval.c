#include "eval.h"

#include "../Game/piece.h"

int eval_material(piece (*obj)[8][8])
{
    int row, col, eval;
    char symbol;

    eval = 0;

    for(row = 0; row < 8; row++) {
        for(col = 0; col < 8; col++) {
            symbol = (*obj)[row][col].name;
            if((*obj)[row][col].color == 'w') {
                switch(symbol) {
                    case 'P':
                        eval = eval + 1;
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

    return eval;
}
