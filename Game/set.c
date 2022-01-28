#include "set.h"

#include "piece.h"

void set_color(char* color, piece (*obj)[8][8])
{
    //Function to set the color of the pieces
    int row;
    int column;

    switch(color[0]) {
        case 'W':
            for(row = 0;row < 8; row++) {
                for(column = 0; column < 8; column++) {
                    if(row == 0 || row == 1) {
                        (*obj)[row][column].color = 'w';
                    } else if(row == 6 || row == 7) {
                        (*obj)[row][column].color = 'b';
                    }
                }
            }
            break;
        case 'B':
            for(row = 0; row < 8; row++) {
                for(column = 0; column < 8; column++) {
                    if(row == 0 || row == 1) {
                        (*obj)[row][column].color = 'b';
                    } else if(row == 6 || row == 7) {
                        (*obj)[row][column].color = 'w';
                    }
                }
            }
            break;
    }
}

void set_rooks(char* color, piece (*obj)[8][8]) 
{
    if(color[0] == 'W') {
        (*obj)[0][0].name = 'R';
        (*obj)[0][7].name = 'R';
        (*obj)[7][0].name = 'r';
        (*obj)[7][7].name = 'r';
    } else {
        (*obj)[0][0].name = 'r';
        (*obj)[0][7].name = 'r';
        (*obj)[7][0].name = 'R';
        (*obj)[7][7].name = 'R';
    }
}

void set_knights(char* color, piece (*obj)[8][8]) 
{
    if(color[0] == 'W') {
        (*obj)[0][1].name = 'N';
        (*obj)[0][6].name = 'N';
        (*obj)[7][1].name = 'n';
        (*obj)[7][6].name = 'n';
    } else {
        (*obj)[0][1].name = 'n';
        (*obj)[0][6].name = 'n';
        (*obj)[7][1].name = 'N';
        (*obj)[7][6].name = 'N';
    }
}

void set_bishops(char* color, piece (*obj)[8][8]) 
{
    if(color[0] == 'W') {
        (*obj)[0][2].name = 'B';
        (*obj)[0][5].name = 'B';
        (*obj)[7][2].name = 'b';
        (*obj)[7][5].name = 'b';
    } else {
        (*obj)[0][2].name = 'b';
        (*obj)[0][5].name = 'b';
        (*obj)[7][2].name = 'B';
        (*obj)[7][5].name = 'B';
    }
}

void set_pawns(char* color, piece (*obj)[8][8])
{
    int square;
  
    if(color[0] == 'W') {
        for(square = 0; square < 8; square++) {
            (*obj)[1][square].name = 'P';
        }
        for(square = 0; square < 8; square++) {
            (*obj)[6][square].name = 'p';
        }
    } else {
        for(square = 0; square < 8; square++) {
            (*obj)[1][square].name = 'p';
        }
        for(square = 0; square < 8; square++) {
            (*obj)[6][square].name = 'P';
        }
    }  
}

void set_queens(char* color, piece (*obj)[8][8])
{
    if(color[0] == 'W') {
        (*obj)[0][3].name = 'Q';
        (*obj)[7][3].name = 'q';
    } else {
        (*obj)[0][4].name = 'q';
        (*obj)[7][4].name = 'Q';
    }
}

void set_kings(char* color, piece (*obj)[8][8])
{
    if(color[0] == 'W') {
        (*obj)[0][4].name = 'K';
        (*obj)[7][4].name = 'k';
    } else {
        (*obj)[0][3].name = 'k';
        (*obj)[7][3].name = 'K';
    }
}

void set_blank(piece (*obj)[8][8])
{
    for(int r = 2; r < 6; r++) {
        for(int i = 0; i < 8; i++) {
            (*obj)[r][i].name = ' ';
        }
    }
}

void set_pieces(char* color, piece (*obj)[8][8])
{
    //Function to group the other set functions

    set_color(color, obj);
    set_rooks(color, obj);
    set_knights(color, obj);
    set_bishops(color, obj);
    set_pawns(color, obj);
    set_queens(color, obj);
    set_kings(color, obj);
    set_blank(obj);
}
