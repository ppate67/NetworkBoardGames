class piece: public chessGame{
private:
    int pieceColor; // 0 = white, 1 = black
    int *location;
public:
    piece(){}
};

class tile: public chessGame{
private:
    int tileColor; // 0 = white, 1 = black
    bool open;
    int *location;
public:

};

class king: public piece{
private:
    bool alive; // is the piece still in the game
    const int value = 1000; // each piece has a different value
public:
    king(Player p){
        alive = true;
        pieceColor = p.userColor; // what color is this piece
        if (pieceColor == 1){
            location = &board[0][4]; // black starts on one side of the board
        }
        else {
            location = &board[7][4]; // white starts on the other
        }
    }
    void allowedMove(){

    }
    void movePiece(){

    }
};

class queen: public piece{
private:
    bool alive;
    const int value = 500;
public:

};

class rook: public piece{
private:
    bool alive;
    const int value = 200;
public:

};

class bishop: public piece{
private:
    bool alive;
    const int value = 100;
public:

};

class knight: public piece{
private:
    bool alive;
    const int value = 50;
public:

};

class pawn: public piece{
private:
    bool alive;
    const int value = 1;
public:

};
