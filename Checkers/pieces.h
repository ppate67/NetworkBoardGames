#ifndef PIECES_H
#define PIECES_H

#include "checkers.h"
#include "checkersboard.h"

class Piece: public Checkers {
private:
    int color;
    char name;
    int row, col;
public:
    Piece(int color, char name, int row, int col): color(color), name(name), row(row), col(col){}
    bool checkValid(int endRow, int endCol, int endPieceColor, bool occupied);
    bool checkPiece(int startRow, int startCol, int endRow, int endCol);
    bool checkKinged(int startRow, int startCol, int endRow, int endCol);

};

#endif // PIECES_H
