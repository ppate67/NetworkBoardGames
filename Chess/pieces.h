#ifndef PIECES_H
#define PIECES_H

class piece: public Chess{
private:
    int color, row, col;
    char name;
public:
    piece(int color, char name, int row, int col): color(color), name(name), row(row), col(col){}
    bool checkValid(piece p, int endRow, int endCol, int endPieceColor);
};

class king: public piece{
public:
    king(){}
    bool allowedMove(int srow, int scol, int erow, int ecol);
};

class queen: public piece{
public:
    queen(){}
    bool allowedMove(int srow, int scol, int erow, int ecol);
};

class rook: public piece{
public:
    rook(){}
    bool allowedMove(int srow, int scol, int erow, int ecol);
};

class bishop: public piece{
public:
    bishop(){}
    bool allowedMove(int srow, int scol, int erow, int ecol);
};

class knight: public piece{
public:
    knight(){}
    bool allowedMove(int srow, int scol, int erow, int ecol);
};

class pawn: public piece{
public:
    pawn(){}
    bool allowedMove(int srow, int scol, int erow, int ecol);
};

#endif
