#ifndef PIECES_H
#define PIECES_H

#include "chess.h"
#include "chessboard.h"

class Piece: public Chess{
private:
    int color;
    char name;
    int row, col;
public:
    Piece(int color, char name, int row, int col): color(color), name(name), row(row), col(col){}
    bool checkValid(int endRow, int endCol, int endPieceColor, bool occupied);
    bool checkPawn(int startRow, int startCol, int endRow, int endCol, bool occupied);
    bool checkRook(int startRow, int startCol, int endRow, int endCol);
    bool checkKnight(int startRow, int startCol, int endRow, int endCol);
    bool checkKing(int startRow, int startCol, int endRow, int endCol);
    bool checkQueen(int startRow, int startCol, int endRow, int endCol);
    bool checkBishop(int startRow, int startCol, int endRow, int endCol);
};

#endif
