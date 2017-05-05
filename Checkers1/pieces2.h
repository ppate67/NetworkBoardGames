#ifndef CPIECES_H
#define CPIECES_H

#include "checkers.h"

class CheckerPiece: public Checkers {
private:
    int color;
    char name;
    int row, col;
public:
    CheckerPiece(int color, char name, int row, int col): color(color), name(name), row(row), col(col){}
    bool checkValid2(int endRow, int endCol, int endPieceColor, bool occupied);
    bool checkPiece2(int startRow, int startCol, int endRow, int endCol);
    bool checkKinged2(int startRow, int startCol, int endRow, int endCol);
    bool checkCapture(int endRow, int endCol, bool midOccupied, bool endOccupied, int midColor);
    bool checkMoves(Checkers* tile[8][8]);

};

#endif // CPIECES_H
