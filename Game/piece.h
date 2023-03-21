#ifndef PIECE_H
#define PIECE_H

struct Piece {
    char color;
    char name;
    int enpassant;
};

typedef struct Piece piece;

#endif
