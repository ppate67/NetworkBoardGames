#include <iostream>
#include <cmath>
#include <CHESSBOARD_H>

class castling: public chessboard{
private:
    bool whitecastled, blackcastled, whiterookMoved0, whiterookMoved7, blackrookMoved0, blackrookMoved7, whitekingMoved, blackkingMoved;
public:
    castling(bool whitecastled, bool blackcastled, bool whiterookMoved0, bool whiterookMoved7, bool blackrookMoved0, bool blackrookMoved7, bool whitekingMoved, bool blackkingMoved):{}
    bool beAttack(chessBoard b, int x, int y, Side side){}
    void MarkrootMoved( chessBoard side, int x, int y){
        if(side==WHITE){
            if(x==0){
                if(y==0){
                    whiterookMoved0=true;
                }
                if(y==7){
                    whiterookMoved0=true;
                }
            }
            return ;
        }
        if(side==BLACK){
            if(y==0){
                blackrookMoved0=true;
            }
            if(y==7){
                blackrookMoved7=true;
            }
        }
    }
    bool CanCastle ( chessBoard b, Side side, int flag){
        int row, i;
        if(side==White){
            row=0;
        }
        else{
            row=7;
        }
        if(flag==5){
            for(i=1;i<4;i++){
                if(b[row][i].i!=NONE){
                    return false;//if there arepieces between king and rook
                }
            }
            for(i=0;i<5;i++){
                if(beAttack(b, row, i, side)){
                    return false;//attacked at the target
                }
            }
            else{
                for(i=5;i<7;i++){
                    if(b[row][i].side!=NONE){
                        return false;
                    }
                }
                for(i=4;i<=7;i++){
                    if(beAttack(b, row, i, side)){
                        return false;
                    }
                }
            }
        }
        if(side==White){
            if(whitekingMoved==true){
                return false;
            }
            else if(flag==3&&whiterookMoved7==true){
                return false;//white rook moved
            }
            else if(flag==5&&whiterookMoved0=true){
                return false;//white rook moved
            }
        }
        else{
            if(blackkingMoved==true){
                return false;
            }
            else if(flag==3&&blackrookMoved7==true){
                return false;
            }
            else if (flag==5&&blackrookMoved0==true){
                return false;
            }
        }
        return true;
    }
};
int main(){

}
