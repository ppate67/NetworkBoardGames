#ifndef CHECKERS_AI_H
#define CHECKERS_AI_H
#include <vector>

class checkers_ai{
private:
    double val=1;                   //AI set value of a piece to determine what to sacrifice
    int row;                        //Used to adjust value based on distance to being kinged
    bool isKing=false  ;            //Value for whether a piece is a king or not
    bool back_row;                  //Special value for back row pieces
    static bool quit=false;
public:
    checkers_ai();


    //Updates a piece's value attribute
    double updateVal(piece){          //get class from checkers
        double orig=piece.val;
        if(!isKing){                //Adjust value based on row and backrow
            if(!back_row){          //Back row is valueable without moving
                piece.val=row*2;
            }
            else{
                piece.val=15;
            }
        }
        else{
            piece.val=50;           //Kings are most valuable
        }
        return piece.val-orig;
    }



};
class possible_move{
private:
    bool isSafe,makeKing,riskKing;
    int val_change,kill,killKing;
    //Placeholder for move values
public:
    possible_move();               //need class from checkers mechanics to test move validity

    //function to pick the best move and send to the server
    void sortMove(vector<possible_move*>& moveList){  //take array of points to possible_move objects
        vector<possible_move*> safeMoves;
        vector<possible_move*> riskMoves;
        if(moveList.size()>0){
            for(int entry=0;entry<moveList.size();){
                if ((*moveList[entry]).isSafe){
                    safeMoves.push_back(moveList[entry]);           //adds safe moves to their own list for use.
                    moveList.erase(moveList.begin() + entry);       //removes safe moves from the movelist
                                                                    //Don't increment if you delete element
                }
                else if((*moveList[entry]).riskKing){
                    riskMoves.push_back(moveList[entry]);           //adds risky moves to their own list for use.
                    moveList.erase(moveList.begin() + entry);       //removes risky move from movelist
                }
                else{
                    entry++;                                        //incrememnt since we didn't delete an entry
                }
            }
        }
        else{
            quit=true;
        }
    }


    possible_move selectMove(vector<possible_move*>& moveList,vector<possible_move*>& safeMoves,vector<possible_move*>& riskMoves){ //return a move
        //current model does not track kill shots. Need to add that
        possible_move* safe,risk,neutral;
        //sort and evaluate neutral moves
        if(moveList.size()>0){
            neutral=moveList[0];                                        //set to first move in the list
            if(moveList.size()>1){
                for(int entry=1;entry<moveList.size();entry++){         //if more than one list check which is best
                    if((neutral*).val_change<(moveList[entry]*).val_change){
                        neutral=moveList[entry];
                    }
                }
            }
        }
        else{
            neutral=nullptr;
        }//close neutral move selection


        if(safeMoves.size()>0){
            safe=safeMoves[0];                                        //set to first move in the list
            if(safeMoves.size()>1){
                for(int entry=1;entry<safeMoves.size();entry++){         //if more than one list check which is best
                    if((safe*).val_change<(safeMoves[entry]*).val_change){
                        safe=safeMoves[entry];
                    }
                }
            }
        }
        else{
            safe=nullptr;
        }//close safe move selection


        if(riskMoves.size()>0){
            risk=riskMoves[0];                                        //set to first move in the list
            if(riskMoves.size()>1){
                for(int entry=1;entry<riskMoves.size();entry++){         //if more than one list check which is best
                    if((risk*).riskKing){                               //check if current move is risking a king
                        if(!(riskMoves[entry]*).riskKing){              //check if next move also risks king
                            risk=riskMoves[entry];                      //move found that doesn't risk king
                        }
                        else{
                            if((risk*).val_change<(riskMoves[entry]*).val_change){      //pick best of king risking moves
                                risk=riskMoves[entry];
                            }
                        }
                    }
                    else{
                        if(!(riskMoves[entry]*).riskKing){              //ignore all moves that risk king if current move doens't
                            if((risk*).val_change<(riskMoves[entry]*).val_change){      //pick best of those moves
                                risk=riskMoves[entry];
                            }
                        }
                    }
                }
            }
        }
        else{
            risk=nullptr;
        }//close risk move selection


        selectBest(safe,risk,neutral);
    }


    possible_move* selectBest(const possible_move* safe,const possible_move* risk,const possible_move* neutral){
        //perhaps make this configurable for "difficulty" use
        //currently plays safe, then neutral, then risk. Should weight options but may make mores sense in chess than checkers.
        if(safe!=nullptr){
            return safe;
        }
        else if(neutral!=nullptr){
            return neutral;
        }
        else{
            return risk;
        }
    }

};

#endif // CHECKERS_AI_H
