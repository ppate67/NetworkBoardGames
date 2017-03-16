#ifndef PIECES_H
#define PIECES_H

#include "chess.h"

class Piece: public Chess{
private:
    int color;
    char name;
    int row, col;
public:
    Piece(int color, char name, int row, int col): color(color), name(name), row(row), col(col){}
    bool checkValid(int endRow, int endCol, int endPieceColor, bool occupied);
    bool checkPawn(int endRow, int endCol, bool occupied);
    bool checkRook(int endRow, int endCol);
    bool checkKnight(int endRow, int endCol);
    bool checkKing(int endRow, int endCol);
    bool checkQueen(int endRow, int endCol);
    bool checkBishop(int endRow, int endCol);
};

#endif
