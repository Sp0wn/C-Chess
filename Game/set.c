#include "set.h"

#include "piece.h"
#include <ctype.h>

void set_color(piece (*obj)[8][8])
{
    int row, column;

    for(row = 0;row < 8; row++) {
        for(column = 0; column < 8; column++) {
            if(row == 0 || row == 1) {
                (*obj)[row][column].color = 'w';
            } else if(row == 6 || row == 7) {
                (*obj)[row][column].color = 'b';
            }
        }
    }
}

void set_enpassant(piece (*obj)[8][8])
{
    int row, column;

    for(row = 0;row < 8; row++) {
        for(column = 0; column < 8; column++) {
            (*obj)[row][column].enpassant = 0;
        }
    }
}

void set_rooks(piece (*obj)[8][8]) 
{
    (*obj)[0][0].name = 'R';
    (*obj)[0][7].name = 'R';
    (*obj)[7][0].name = 'r';
    (*obj)[7][7].name = 'r';
}

void set_knights(piece (*obj)[8][8]) 
{
    (*obj)[0][1].name = 'N';
    (*obj)[0][6].name = 'N';
    (*obj)[7][1].name = 'n';
    (*obj)[7][6].name = 'n';
}

void set_bishops(piece (*obj)[8][8]) 
{
    (*obj)[0][2].name = 'B';
    (*obj)[0][5].name = 'B';
    (*obj)[7][2].name = 'b';
    (*obj)[7][5].name = 'b';
}

void set_pawns(piece (*obj)[8][8])
{
    int square;
    for(square = 0; square < 8; square++) {
        (*obj)[1][square].name = 'P';
    }
    for(square = 0; square < 8; square++) {
    (*obj)[6][square].name = 'p';
    }
}

void set_queens(piece (*obj)[8][8])
{
    (*obj)[0][3].name = 'Q';
    (*obj)[7][3].name = 'q';
}

void set_kings(piece (*obj)[8][8])
{
    (*obj)[0][4].name = 'K';
    (*obj)[7][4].name = 'k';
}

void set_blank(piece (*obj)[8][8])
{
    for(int r = 2; r < 6; r++) {
        for(int i = 0; i < 8; i++) {
            (*obj)[r][i].name = ' ';
        }
    }
}

void set_pieces(piece (*obj)[8][8])
{
    set_color(obj);
    set_enpassant(obj);
    set_rooks(obj);
    set_knights(obj);
    set_bishops(obj);
    set_pawns(obj);
    set_queens(obj);
    set_kings(obj);
    set_blank(obj);
}

void read_FEN(piece (*obj)[8][8], char *FEN)
{
    int row, col, index, space;

    index = 0;

    for(row = 7; row >= 0; row--) {
        col = 0;
        while(FEN[index] != '/' && FEN[index] != '\0') {
            if(isdigit(FEN[index]) != 0) {
                for(space = 0; space < (FEN[index] - 48); space++) {
                    (*obj)[row][col].name = ' ';
                    col++;
                }
            } else {
                (*obj)[row][col].name = FEN[index];
                if(isupper(FEN[index]) != 0) {
                    (*obj)[row][col].color = 'w';
                } else {
                    (*obj)[row][col].color = 'b';
                }
                col++;
            }
            index++;
        }
        index++;
    }       
}
