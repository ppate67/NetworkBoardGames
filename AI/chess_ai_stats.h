#ifndef CHESS_AI_STATS_H
#define CHESS_AI_STATS_H


class Chess_AI
{
private:
    //decide if AI should forfeit
    static bool quit;
    //Assign piece value
    const static double king_val=100;
    const static double queen_val=50;
    const static double rook_val=35;
    const static double bishop_val=20;
    const static double knight_val=15;
    double pawn_val=3;

    //Assign piece mobility
    const static double king_mob=10;
    const static double queen_mob=100;
    const static double rook_mob=50;
    const static double bishop_mob=35;
    const static double knight_mob=45;
    const static double pawn_mob=3;



public:
    Chess_AI();
    void updateVal(){}  //placeholder for updating value of pawn based on progress. Pawns about to reach enemy side should be almost as valuable as a queen.
    vector<possible_move*> moveList;
};

class possible_move:Chess_AI{    //class for creating possible moves
private:
    bool isCheck,isCheckMate;               //tracks if a move creates check/checkmate against enemy
    int rPawn,rKnight,rBishop,rRook,rQueen; //track if move risks own peices. May want to only track new risks?
    int kill; //track if move kills enemy peice, 0:None, 1:Pawn, 2:Knight, 3:Bishop, 4:Rook, 5:Queen
    double valChange;
public:
    possible_move();
    possible_move sortMove(){}


    double netChange(const possible_move& move,double& valChange){
        switch(kill){
        case 0: break;      //may want to handle non kill moves differently
        case 1:
            double pawnVal=checkPawnVal(); //check if enemy pawn is nearing upgrade
            valChange=(pawnVal)-(rPawn*move.pawn_val)-(rKnight*move.knight_val)-(rBishop*move.bishop_val)-(rRook*move.rook_val)-(rQueen*move.queen_val);
            break;
        case 2:
            valChange=(move.knight_val)-(rPawn*move.pawn_val)-(rKnight*move.knight_val)-(rBishop*move.bishop_val)-(rRook*move.rook_val)-(rQueen*move.queen_val);
        case 3:
            valChange=(move.bishop_val)-(rPawn*move.pawn_val)-(rKnight*move.knight_val)-(rBishop*move.bishop_val)-(rRook*move.rook_val)-(rQueen*move.queen_val);
        case 4:
            valChange=(move.rook_val)-(rPawn*move.pawn_val)-(rKnight*move.knight_val)-(rBishop*move.bishop_val)-(rRook*move.rook_val)-(rQueen*move.queen_val);
        case 5:
            valChange=(move.queen_val)-(rPawn*move.pawn_val)-(rKnight*move.knight_val)-(rBishop*move.bishop_val)-(rRook*move.rook_val)-(rQueen*move.queen_val);
        }
    }



};

#endif // CHESS_AI_STATS_H
