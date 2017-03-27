#ifndef CHESS_AI_STATS_H
#define CHESS_AI_STATS_H


class Chess_AI
{
private:
    //decide if AI should forfeit
    static bool quit;
    //Assign piece value
    double king_val=100;
    double queen_val=50;
    double rook_val=35;
    double bishop_val=20;
    double knight_val=15;
    double pawn_val=3;

    //Assign piece mobility
    double king_mob=10;
    double queen_mob=100;
    double rook_mob=50;
    double bishop_mob=35;
    double knight_mob=45;
    double pawn_mob=3;


public:
    Chess_AI();
};

#endif // CHESS_AI_STATS_H
