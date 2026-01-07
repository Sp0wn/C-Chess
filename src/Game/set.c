//File guard
#include "../../include/Game/set.h"

void set_pawns(Board* board) {
    int square;
    for(square = 0; square < 8; square++) {
        board[1][square]->name = 'P';
    }
    for(square = 0; square < 8; square++) {
        board[6][square]->name = 'p';
    }
}

void set_rooks(Board* board) {
    board[0][0]->name = 'R';
    board[0][7]->name = 'R';
    board[7][0]->name = 'r';
    board[7][7]->name = 'r';
}

void set_kings(Board* board) {
    board[0][4]->name = 'K';
    board[7][4]->name = 'k';
}

void set_queens(Board* board) {
    board[0][3]->name = 'Q';
    board[7][3]->name = 'q';
}

void set_bishops(Board* board) {
    board[0][2]->name = 'B';
    board[0][5]->name = 'B';
    board[7][2]->name = 'b';
    board[7][5]->name = 'b';
}

void set_knights(Board* board) {
    board[0][1]->name = 'N';
    board[0][6]->name = 'N';
    board[7][1]->name = 'n';
    board[7][6]->name = 'n';
}

void set_pieces_color(Board* board) {
    int row, column;

    for(row = 0; row < 8; row++) {
        for(column = 0; column < 8; column++) {
            if(row == 0 || row == 1) {
                board[row][column]->color = 'w';
            } else if (row == 6 || row == 7) {
                board[row][column]->color = 'b';
            }
        }
    }
}

void set_pieces_empty(Board* board) {
    int row, column;
    for(row = 2; row < 6; row++) {
        for(column = 0; column < 8; column++) {
            board[row][column]->name = ' ';
        }
    }
}

void set_pieces(Board* board) {
    set_pawns(board);
    set_rooks(board);
    set_kings(board);
    set_queens(board);
    set_bishops(board);
    set_knights(board);
    set_pieces_color(board);
    set_pieces_empty(board);
}
