#ifndef PIECE_H
#define PIECE_H

struct Piece {
  char color;
  char name;
};

typedef struct Piece piece;

extern const piece reset_p;

#endif
