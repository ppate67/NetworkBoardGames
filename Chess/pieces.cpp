#include "pieces.h"

bool king::allowedMove(int srow, int scol, int erow, int ecol){
    
}

bool piece::checkValid(piece p, int endRow, int endCol, int endPieceColor){
    if(p.color == endPieceColor){
        return false;
    }
    bool allow = false;
    swtich(p.name){
        case 'P': allow = pawn::allowedMove(p.row, p.col, endRow, endCol);
            break;
        case 'R': allow = rook::allowedMove(p.row, p.col, endRow, endCol);
            break;
        case 'H': allow = knight::allowedMove(p.row, p.col, endRow, endCol);
            break;
        case 'K': allow = king::allowedMove(p.row, p.col, endRow, endCol);
            break;
        case 'Q': allow = queen::allowedMove(p.row, p.col, endRow, endCol);
            break;
        case 'B': allow = bishop::allowedMove(p.row, p.col, endRow, endCol);
            break;
   }
   return allow;
}
