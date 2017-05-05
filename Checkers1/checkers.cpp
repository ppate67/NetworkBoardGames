#include "Checkers1/pieces2.h"
#include "Checkers1/checkersboard.h"
#include "iostream"
#include <sstream>

#include "QMessageBox"
Checkers *temp2;
int Checkers::selected=0;
Checkers* Checkers::checkershead=NULL;
int Checkers::checkersturn=1;
int Checkers::playercolor=0;
int Checkers::offline=0;
bool Checkers::multicap=false;
void Checkers::mousePressEvent(QMouseEvent *event)
{
    if(selected==0)
    {
        if (getPiece() == false|| this->getPieceColor()!=Checkers::playercolor|| checkersturn==0){
            selected = 0;
        }
        else {
            this->getPieceName();
            this->setStyleSheet("QLabel {background-color:rgb(176, 255, 20);}");
            selected=1;
            temp2=this;
        }
    }
    else
    {
        // give selected color, name, row, and column to piece object
        CheckerPiece p(temp2->getPieceColor(), temp2->getPieceName(), temp2->getRow(), temp2->getColumn());
        // clicked back on itself so allow a new choice
        if (this->getTileNum() == temp2->getTileNum()){
            selected = 0;
            temp2->displayBoard();
            if(multicap==true){
                multicap=false;
                if(offline==0)
                    sendGameMsg();
                else
                    passToAI();
            }
        }
        // check piece with ending location to see if move is valid;
        else if (p.checkValid2(this->getRow(), this->getColumn(), this->getPieceColor(), this->getPiece()) == true && !multicap){
            
            selected=0;
            //this->setTileColor(temp2->getTileColor());
            this->setPieceColor(temp2->getPieceColor());
            this->setPiece(true);
            this->setpieceName(temp2->getPieceName());
            if(this->getRow()==0 && this->getPieceColor()==1)
                this->setpieceName('K');
            else if(this->getRow()==7 && this->getPieceColor()==0)
                this->setpieceName('K');
            temp2->displayBoard();
            this->displayElement(this->getPieceName());
            temp2->setPiece(false);
            temp2->displayElement(' ');
            temp2->displayBoard();
            if(offline==0)
                sendGameMsg();
            else
                passToAI();
        }
        else if (abs(this->getRow()-temp2->getRow())==2 && abs(this->getColumn()-temp2->getColumn())==2){
            bool middleOccupied = checkersboard::tile[(this->getRow()+temp2->getRow())/2][(this->getColumn()+temp2->getColumn())/2]->getPiece();

            Checkers* middlepiece = checkersboard::tile[(this->getRow()+temp2->getRow())/2][(this->getColumn()+temp2->getColumn())/2];
            if(p.checkCapture(this->getRow(), this->getColumn(), middleOccupied, this->getPiece(), middlepiece->getPieceColor())){//&& ((middlepiece->row+1)==this->row || (middlepiece->row+1)==temp2->row)&&((middlepiece->col+1)==this->col || (middlepiece->col+1)==temp2->col)){
                //this checks for capture. if valid capture it executes capture, prints board, sends game message over socket
                selected=0;
                this->setPieceColor(temp2->getPieceColor());
                this->setPiece(true);
                this->setpieceName(temp2->getPieceName());
                if(this->getRow()==0 && this->getPieceColor()==1)
                    this->setpieceName('K');
                else if(this->getRow()==7 && this->getPieceColor()==0)
                    this->setpieceName('K');
                temp2->displayBoard();
                this->displayElement(this->getPieceName());
                temp2->setPiece(false);
                temp2->displayElement(' ');
                temp2->displayBoard();
                middlepiece->setPiece(false);
                middlepiece->setpieceName(' ');
                middlepiece->displayElement(' ');
                middlepiece->displayBoard();
                if(!multiCapture()){
                    multicap=false;
                    this->displayBoard();
                    if(offline==0)
                        sendGameMsg();
                    else
                        passToAI();
                }
                if(checkForWin(this->getPieceColor())){
                    //End game, notify players of winner.
                    //For now I'm testing with a console print.
                    cout << "Game over." << endl;
                }
            }
            
        }
    }
}
bool Checkers::multiCapture(){
    Checkers* topright=nullptr; Checkers* bottomright=nullptr; Checkers* topleft=nullptr;Checkers* bottomleft=nullptr;
    if(this->row>=2 && this->col<=5){
        topright=checkersboard::tile[this->row-2][this->col+2];

        CheckerPiece p(this->getPieceColor(), this->getPieceName(), this->getRow(), this->getColumn());
        bool middleOccupied = checkersboard::tile[(this->getRow()+topright->getRow())/2][(this->getColumn()+topright->getColumn())/2]->getPiece();

        Checkers* middlepiece = checkersboard::tile[(this->getRow()+topright->getRow())/2][(this->getColumn()+topright->getColumn())/2];
        if(p.checkCapture(topright->row,topright->col,middleOccupied,topright->getPiece(), middlepiece->getPieceColor())){
            multicap=true;
            selected=1;
            temp2=this;
            this->getPieceName();
            this->setStyleSheet("QLabel {background-color:rgb(176, 255, 20);}");
            return true;
        }

    }
    if(this->row<=5 && this->col<=5){
       bottomright=checkersboard::tile[this->row+2][this->col+2];
       CheckerPiece p(this->getPieceColor(), this->getPieceName(), this->getRow(), this->getColumn());
       bool middleOccupied = checkersboard::tile[(this->getRow()+bottomright->getRow())/2][(this->getColumn()+bottomright->getColumn())/2]->getPiece();

       Checkers* middlepiece = checkersboard::tile[(this->getRow()+bottomright->getRow())/2][(this->getColumn()+bottomright->getColumn())/2];
       if(p.checkCapture(bottomright->row,bottomright->col,middleOccupied,bottomright->getPiece(), middlepiece->getPieceColor())){
           multicap=true;
           selected=1;
           temp2=this;
           this->getPieceName();
           this->setStyleSheet("QLabel {background-color:rgb(176, 255, 20);}");
           return true;
       }

    }
    if(this->row>=2 && this->col>=2){
        topleft=checkersboard::tile[this->row-2][this->col-2];
        CheckerPiece p(this->getPieceColor(), this->getPieceName(), this->getRow(), this->getColumn());
        bool middleOccupied = checkersboard::tile[(this->getRow()+topleft->getRow())/2][(this->getColumn()+topleft->getColumn())/2]->getPiece();

        Checkers* middlepiece = checkersboard::tile[(this->getRow()+topleft->getRow())/2][(this->getColumn()+topleft->getColumn())/2];
        if(p.checkCapture(topleft->row,topleft->col,middleOccupied,topleft->getPiece(), middlepiece->getPieceColor())){
            multicap=true;
            selected=1;
            temp2=this;
            this->getPieceName();
            this->setStyleSheet("QLabel {background-color:rgb(176, 255, 20);}");
            return true;
        }

    }
    if(this->row<=5 && this->col>=2){
        bottomleft=checkersboard::tile[this->row+2][this->col-2];
        CheckerPiece p(this->getPieceColor(), this->getPieceName(), this->getRow(), this->getColumn());
        bool middleOccupied = checkersboard::tile[(this->getRow()+bottomleft->getRow())/2][(this->getColumn()+bottomleft->getColumn())/2]->getPiece();

        Checkers* middlepiece = checkersboard::tile[(this->getRow()+bottomleft->getRow())/2][(this->getColumn()+bottomleft->getColumn())/2];
        if(p.checkCapture(bottomleft->row,bottomleft->col,middleOccupied,bottomleft->getPiece(), middlepiece->getPieceColor())){
            multicap=true;
            selected=1;
            temp2=this;
            this->getPieceName();
            this->setStyleSheet("QLabel {background-color:rgb(176, 255, 20);}");
            return true;
        }

    }
    return false;
}

bool Checkers::checkForWin(int lastMoveColor){
    //Go through each element on the board. If there are no opponent color pieces remaining, return true.
    //Not efficient, but without keeping a static count of how many of each color are left, this is the easiest.
    for(int i = 0; i < 8; i++)
        for(int j = 0; j < 8; j++)
            if(checkersboard::tile[i][j]->getPiece() == true && checkersboard::tile[i][j]->getPieceColor() != lastMoveColor)
                return false;
    if(openMoves(lastMoveColor))
        return false;
    return true;
}

bool Checkers::openMoves(int lastMoveColor){
    //Go through each element of the board. If there are no pieces with available moves remaining
    //(i.e. all opponent pieces are blocked) that player loses.
    for(int i = 0; i < 8; i++)
        for(int j = 0; j < 8; j++){
            if(checkersboard::tile[i][j]->getPiece() == true && checkersboard::tile[i][j]->getPieceColor() != lastMoveColor){
                CheckerPiece p(checkersboard::tile[i][j]->getPieceColor(), checkersboard::tile[i][j]->getPieceName(), i, j);
                if(p.checkMoves(checkersboard::tile))
                    return true;
            }
            else
                continue;
        }
    return false;
}

void Checkers::displayElement(char elem)
{
    /*
        This method simply changes the picture displayed by the label with the specified Checkers piece name value denoted by char elem.


    */
    this->pieceName=elem;
    this->setScaledContents(true);
    if(this->pieceColor==1 && this->piece==true)
    {
        switch(elem)
        {
        case 'K': this->setPixmap(QPixmap(":/IconsCheckers/redking.png"));
            break;
        case 'P': this->setPixmap(QPixmap(":/IconsCheckers/redpiece.png"));
            break;

        }
    }

    else if(this->piece==true)
    {
        switch(elem)
        {
        case 'P': this->setPixmap(QPixmap(":/IconsCheckers/blackpiece.png"));
            break;
        case 'K': this->setPixmap(QPixmap(":/IconsCheckers/blackking.png"));
            break;
        }
    }
    else
        this->clear();
}


void Checkers::displayBoard()
{
    /*
        This method sets the tile colors in the alternating checkered format.
    */
    if(this->tileColor==1)
    {
        this->setStyleSheet("QLabel {background-color:rgb(255, 193, 122);}:hover{background-color: rgb(62, 139, 178);}");
    }
    else
    {
        this->setStyleSheet("QLabel {background-color:rgb(147, 91, 26);}:hover{background-color: rgb(62, 139, 178);}");
    }
}
void Checkers::capturePiece(Checkers* capturee, Checkers* captor){
    //captures piece (i.e. removes it from the board)
    //we then check if the player is able to capture an additional piece
    //this depends on piece type and piece color
    //we will have a timer or button that allows the player to make multistage move. For now a simple pop-up message asking
    // if they want to make an additional move will suffice. The graphics team can make it look nicer
    selected=0;
    this->setPieceColor(Checkers::playercolor);
    this->setPiece(true);
    this->setpieceName(captor->getPieceName());
    if(this->getRow()==0 && this->getPieceColor()==1)
        this->setpieceName('K');//promotion via capture for red
    else if(this->getRow()==7 && this->getPieceColor()==0)
        this->setpieceName('K');//promotion via capture for black
    captor->displayBoard();
    this->displayElement(this->getPieceName());
    captor->setPiece(false);
    captor->displayElement(' ');
    captor->displayBoard();
    capturee->setPiece(false);
    capturee->displayElement(' ');
    capturee->displayBoard();
    //need to add multistage move
    sendGameMsg();
}
void Checkers::checkCapture(){

    //this function is called to check if a move is valid in a capture scenario
    //this functionality isn't covered by any methods in the CheckerPiece class
    //and it would be easier to do it here since the entire checkers data strut is here to work with
    //we will call capturePiece if we find it is a valid capture

    int usercolor= temp2->getPieceColor();
    int enemycolor=0;
    if(enemycolor==usercolor)enemycolor++;
    if(temp2->getPieceName()=='K'){
        if(this->row > temp2->row){
            captureAuxiloryFunc(1,enemycolor);
        }
        if(this->row<temp2->row){
            captureAuxiloryFunc(0,enemycolor);//this is hacky but it is a valid approach --better
        }
    }
    else{
        if(usercolor==0){//black pieces increasing numbers in rows
                captureAuxiloryFunc(0,1);
        }
        else if(usercolor==1){//red pieces decreasing numbers in rows
            captureAuxiloryFunc(1,0);
        }
    }

}
void Checkers::captureAuxiloryFunc(int usercolor, int enemycolor){
    if(usercolor==1){

        if(this->row < temp2->row){
            Checkers* bwalk=this;//backward list walk
            Checkers* fwalk=temp2;//forward list walk
            Checkers* topleft=temp2;
            Checkers* topright=temp2;
            Checkers* blselecteddes=this;//this will become the bottom left of the selected destination. If it equals topright then it's maybe a valid capture
            Checkers* brselecteddes=this;//this will become the bottom right of the selected destination. If it equals topleft then it's maybe a valid capture
            for(int i = 0; i<9; i++){
                fwalk=fwalk->nexttile;
                bwalk=bwalk->prevtile;
                if(i==6){
                    topright=bwalk;
                    blselecteddes=fwalk;
                }
                else if(i==8){
                    topleft=bwalk;
                    brselecteddes=fwalk;
                }


            }
            if(topright==blselecteddes){

                if(topright->getPieceColor()==enemycolor){

                    capturePiece(topright,temp2);
                }
            }
            if(topleft==brselecteddes){

                if(topleft->getPieceColor()==enemycolor){

                    capturePiece(topleft,temp2);
                }
            }
        }
    }
    else if(usercolor==0){

        if(this->row > temp2->row){

            Checkers* bwalk=temp2;//backward list walk
            Checkers* fwalk=this;//forward list walk
            Checkers* tlselecteddes=this;//this will become the top left of the selected destination. If it equals bottomright then it's a valid capture (maybe)
            Checkers* trselecteddes=this;//this will become the top right of the selected destination. If it equals bottomleft then it's a valid capture (maybe)
            Checkers* bottomright=temp2;
            Checkers* bottomleft=temp2;


            for(int i =0; i<9; i++){
                fwalk=fwalk->nexttile;
                bwalk=bwalk->prevtile;
                if(i==6){
                    trselecteddes=bwalk;
                    bottomleft=fwalk;
                }
                else if(i==8){
                    tlselecteddes=bwalk;
                    bottomright=fwalk;
                }


            }

            if(tlselecteddes==bottomright){
                if(bottomright->getPieceColor()==enemycolor){
                    capturePiece(bottomright,temp2);
                }
            }
            if(trselecteddes==bottomleft){
                if(bottomleft->getPieceColor()==enemycolor){
                    capturePiece(bottomleft,temp2);
                }
            }
        }
    }
    else{

    }

}
void Checkers::sendGameMsg(){
    QByteArray BufferPing;
    int des=0;
    int vecsize=GameManager::games.size();

    //this finds gameid by looking up the game the player is currently in
    //currently it doesn't check if it is a checkers game and assumes the player can only be in one game at a time
    for(int i =0; i<vecsize; i++){
        int playsize=GameManager::games[i].size();
        for(int ii=0; ii<playsize;ii++){
            if(GameManager::games[i][ii][2]==GameManager::clientID)
                des=i;
        }
    }
    //build byte array denoted by BufferPing. send it over socket connection when built
    BufferPing.append(char(des));
    BufferPing.append(char(2));//type =2 for Checkers games
    Checkers*tiles[8][8];
    Checkers*pnt=findHead(this);
    fillArray(tiles,findHead(this));

    for(int j=0; j<8;j++){
        for(int i=0;i<8;i++){
            char piecename = tiles[i][j]->getPieceName();
            //if black piece we send it as uppercase letter
            //if white piece we send it as lowercase letter
            //this is so we can distinquish between the two color sets without
            //needing more than 64 bytes
            if(tiles[i][j]->getPieceColor()==1 && tiles[i][j]->getPieceName()!=' ')
                piecename=char(int(piecename)+32);
            BufferPing.append(piecename);

        }
    }

    Client::s->write(BufferPing);
    Client::s->flush();
    Checkers::checkersturn=0;
}
Checkers* Checkers::findHead(Checkers* pnt){
    //finds head of checkers data structure (through use of pointers).
    //Used whenever one needs to traverse the data structure from the top

    while(1){
        if(pnt->prevtile==NULL)
            return pnt;
        pnt=pnt->prevtile;
    }
}
void Checkers::fillArray(Checkers* tiles[8][8],Checkers* pnt){
    //Fills tiles with Checkers pointers in such a way as to geometrically mirror the checkers board in the array
    tiles[0][0]=pnt;
    for(int ii=0;ii<8;ii++){
        for(int i=0;i<8;i++){
            tiles[i][ii]=pnt;
            pnt=pnt->nexttile;
        }

    }

}
void Checkers::receiveUpdates(char piece1, int iteration){

    /*
        This method uses iteration to denote where on the checkers board
        we are updating and piece1 to denote what to update it with.
        The method is called iteratively 64 times in order to update the
        entire board. Capital letters received through piece1 means that the
        color of the piece is of value 0. Lower case are naturally of value 1 then.
        This method also allows the player to take their turn again.



    */
    Checkers*temp=Checkers::checkershead;
    for(int i=0;i<iteration;i++){
        temp=temp->nexttile;
    }
    if(int(piece1)==32){
        temp->setPiece(false);
        temp->clear();
    }
    else{
        temp->setPiece(true);
        if(int(piece1)>90){
            piece1-=32;
            temp->setPieceColor(1);
        }
        else{
            temp->setPieceColor(0);
        }
    }
    temp->setpieceName(piece1);



    temp->displayElement(temp->getPieceName());
    temp->displayBoard();

    int vecsize=GameManager::games.size();
    for(int i =0; i<vecsize; i++){
        int playsize=GameManager::games[i].size();
        for(int ii=0; ii<playsize;ii++){
            if(GameManager::games[i][ii][2]==GameManager::clientID && GameManager::games[i][ii][1]==1)
                Checkers::checkersturn=1;
        }
    }

}
void Checkers::passToAI(){
    /*
        This is a complicated start to a set of methods that do the AI work.
        passToAI first makes four vectors desecribing the pieces on the board and the moves they can make (for each color).
        It then passes those into evaluateMoves which essentially both evaluates moves based on a minimax algorithm (alpha beta pruning)
        and on future moves. The move returned through this method is the move the AI chooses. At the end of this method we see the program implement
        the move in the actual game such that the player can see it.

        Note: This AI is not good. It is slow, inefficient, and unintelligent. This is mainly due to the fact that we inefficiently have defined evaluateMoves in a
        way that requires unnecessary computation and copying. The only way to fix this would be to use complicated methods such as 'bitboards' or boards defined by a set of 64 bits (or a type long).

        This would be too much to implement given the scope of the project.


    */


    int AIcolor = 0; if(playercolor==0) AIcolor=1;
    //make a list of pieces that can make moves and use that list with the
    //possible moves functions for checkers
    Checkers* temp = checkershead;
    vector<Checkers*> posspieces;
    vector<Checkers*> playerpieces;
    vector<vector<int>> moveList;
    vector<vector<int>> playermoves;

    string currentBoardState="";//will use at the end to reset the board state
    while(temp!=nullptr)
    {
                char piecename = temp->getPieceName();
                //if black piece we send it as uppercase letter
                //if white piece we send it as lowercase letter
                //this is so we can distinquish between the two color sets without
                //needing more than 64 bytes
                if(temp->getPieceColor()==1 && temp->getPieceName()!=' ')
                    piecename=char(int(piecename)+32);
                currentBoardState+=(piecename);


        int col = temp->getColumn();
        int row = temp->getRow();
        if(temp->getPieceColor()==AIcolor){
            CheckerPiece p(AIcolor,temp->getPieceName(),row,col);
            vector<int> possibleMoves;

            for(int i =0; i<8; i++)
            {
                for(int ii =0; ii<8; ii++){
                    if(i==row && ii==col);//possibleMoves.push_back(i*8+ii);
                    else{
                        Checkers *targetDes = this->findPiece(i,ii);
                        bool validity=p.checkValid2(i,ii,targetDes->getPieceColor(),targetDes->getPiece());
                        if(validity)
                            possibleMoves.push_back(i*8 + ii);
                        bool middleOccupied = checkersboard::tile[(targetDes->getRow()+temp->getRow())/2][(targetDes->getColumn()+temp->getColumn())/2]->getPiece();

                        Checkers* middlepiece = checkersboard::tile[(targetDes->getRow()+temp->getRow())/2][(targetDes->getColumn()+temp->getColumn())/2];
                        if(p.checkCapture(targetDes->getRow(), targetDes->getColumn(), middleOccupied, targetDes->getPiece(), middlepiece->getPieceColor()))
                            possibleMoves.push_back(i*8 + ii);
                    }


                }
            }

            if(possibleMoves.size()>0){
                moveList.push_back(possibleMoves);
                posspieces.push_back(temp);
            }
        }
        else if(temp->getPieceColor()==playercolor && temp->getPiece())
        {
            CheckerPiece p(playercolor,temp->getPieceName(),row,col);
            vector<int> possibleMoves;

            for(int i =0; i<8; i++)
            {
                for(int ii =0; ii<8; ii++){
                    if(i==row && ii==col);//possibleMoves.push_back(i*8+ii);
                    else{
                        Checkers *targetDes = this->findPiece(i,ii);
                        bool validity=p.checkValid2(i,ii,targetDes->getPieceColor(),targetDes->getPiece());
                        if(validity)
                            possibleMoves.push_back(i*8 + ii);
                    }


                }
            }

            if(possibleMoves.size()>0){
                playermoves.push_back(possibleMoves);
                playerpieces.push_back(temp);
            }


        }
        temp=temp->nexttile;



    }

    vector<int> bestMove = evaluateMoves(currentBoardState,moveList,playermoves,posspieces,playerpieces,0,AIcolor, -10000000,10000000,0);
    int des = bestMove[0];
    Checkers* bestPiece= posspieces[0];
    if(bestMove[2]<posspieces.size())
        bestPiece = posspieces[bestMove[2]];
    Checkers *bestDes = findPiece(des/8,des%8);
    bestPiece->setPiece(false);
    bestDes->setpieceName(bestPiece->getPieceName());
    bestDes->setPiece(true);
    bestPiece->setPieceColor(2);
    bestDes->setPieceColor(AIcolor);
    bestPiece->setpieceName(' ');
    bestPiece->displayElement(' ');

    Checkers* middlepiece = checkersboard::tile[(bestDes->getRow()+bestPiece->getRow())/2][(bestDes->getColumn()+bestPiece->getColumn())/2];
    if(abs(bestDes->getRow()-bestPiece->getRow())==2 && abs(bestDes->getColumn()-bestPiece->getColumn())==2){
        middlepiece->setPiece(false);
        middlepiece->setpieceName(' ');
        middlepiece->setPieceColor(2);
        middlepiece->displayElement(' ');
        middlepiece->displayBoard();
    }
    if(bestDes->getRow()==0 && bestDes->getPieceColor()==1)
        bestDes->setpieceName('K');
    else if(bestDes->getRow()==7 && bestDes->getPieceColor()==0)
        bestDes->setpieceName('K');
    bestDes->displayElement(bestDes->getPieceName());
}
vector<int> Checkers::evaluateMoves(const string& originalBoardState,vector<vector<int>> moves,vector<vector<int>> playermoves, vector<Checkers*> AIpieces,vector<Checkers*> playerpieces, int treelength, int ecolor, int alpha, int beta, int score){//
//returns index of best move and the score of that move. treelength is how far in the future we are evaluating to
    int AIcolor = 0;if(playercolor==0)AIcolor=1;
    int nextColor = 0; if(ecolor==0)nextColor=1;
    int bestPiece= 0;

    int highestPieceScore=-100000000;
    if(AIcolor!=ecolor)//minimizing
        highestPieceScore=1000000000;
    int bestMoveIndex=0;//index of position in moves list relative to the number of pieces. Value/pieces.size() gives actual index in moves vector
    //if(pieces.size()!=moves.size())
        //return{0,0,0};//this means that something is not working
    int numPieces = AIpieces.size(); if(ecolor!=AIcolor)numPieces=playerpieces.size();
    for(int i =0; i<numPieces; i++){
        int movesSetScore=-100000000;
        int bestSetIndex=0;
        if(AIcolor!=ecolor){//minimizing
            movesSetScore=100000000;
        }
        int numMoves = 0;if(ecolor==AIcolor)numMoves=moves[i].size(); if(ecolor!=AIcolor)numMoves=playermoves[i].size();
        for(int ii=0; ii<numMoves; ii++){

            //
            string boardState = this->describeBoardState();

            Checkers* newposs;
            if(AIcolor==ecolor)
                newposs= findPiece(moves[i][ii]/8, moves[i][ii]%8);
            else
                newposs=findPiece(playermoves[i][ii]/8, playermoves[i][ii]%8);
            int multiplier=1;
            if(AIcolor!=ecolor)multiplier=-1;



            int col = newposs->getColumn();
            int row = newposs->getRow();
            int setScore=0;
            if(AIcolor==ecolor){
                setScore=AIpieces[i]->findScore(moves[i][ii]);

                    AIpieces[i]->setPiece(false);
                    newposs->setpieceName(AIpieces[i]->getPieceName());
                    newposs->setPiece(true);
                    newposs->setPieceColor(ecolor);
                    AIpieces[i]->setpieceName(' ');

            }
            else if(AIcolor!=ecolor){
                setScore=playerpieces[i]->findScore(playermoves[i][ii])*-1;

                    playerpieces[i]->setPiece(false);
                    newposs->setpieceName(playerpieces[i]->getPieceName());
                    newposs->setPiece(true);
                    newposs->setPieceColor(ecolor);
                    playerpieces[i]->setpieceName(' ');

            }
            vector<vector<int>>MoveSet;
            vector<Checkers*> pieceSet;

            Checkers* temp = checkershead;

            if(treelength<1){
                vector<Checkers*>temppieces;
                if(AIcolor==nextColor)temppieces=AIpieces;
                else temppieces=playerpieces;
                //temppieces[i]=newposs;
                for(auto temp : temppieces){//while(temp!=nullptr){
                    vector<int>possibleMoves;
                    //possibleMoves=temp->findPossMoves();
                    CheckerPiece p(nextColor,temp->getPieceName(),temp->getRow(),temp->getColumn());
                    for(int j =0; j<8; j++)
                    {
                        for(int jj =0; jj<8; jj++){

                            if(j==row && jj==col);//possibleMoves.push_back(j*8+jj);
                            else{
                                if(temp->getPieceColor()==nextColor){
                                    Checkers *targetDes = this->findPiece(j,jj);
                                    bool validity=p.checkValid2(j,jj,targetDes->getPieceColor(),targetDes->getPiece());
                                    if(validity)
                                        possibleMoves.push_back(j*8 + jj);
                                    bool middleOccupied = checkersboard::tile[(targetDes->getRow()+temp->getRow())/2][(targetDes->getColumn()+temp->getColumn())/2]->getPiece();

                                    Checkers* middlepiece = checkersboard::tile[(targetDes->getRow()+temp->getRow())/2][(targetDes->getColumn()+temp->getColumn())/2];
                                    if(p.checkCapture(targetDes->getRow(), targetDes->getColumn(), middleOccupied, targetDes->getPiece(), middlepiece->getPieceColor()))
                                        possibleMoves.push_back(j*8 + jj);
                                }

                            }


                        }
                    }
                    if(possibleMoves.size()>0){
                        MoveSet.push_back(possibleMoves);
                        pieceSet.push_back(temp);
                    }
                    //temp=temp->nexttile;
                }
            }
            //we want to simulate what the board state is like if we make each of these possible moves
            int nextIterationScore=setScore;
            int nextIterationIndex=0;
            if(treelength<1){
//                    int movesetsize=MoveSet.size();//this would be to randomly get rid of vector data as to make the AI faster
//                    for(int t=0;t<treelength;t++)
//                    for(int tt=0; tt<movesetsize/2;tt++){
//                        int index=rand()%(movesetsize-tt*(t+1));
//                        MoveSet.erase(MoveSet.begin() + index);
//                        pieceSet.erase(pieceSet.begin() + index);
//                    }
                if(ecolor==AIcolor)//maximizer
                {
                    int v = -100000000;
                    score +=setScore;
                    vector<int> nextIter=evaluateMoves(boardState,moves,MoveSet,AIpieces,pieceSet,treelength+1,nextColor, alpha, beta, score);
                    //vector<int> nextIter=evaluateMoves(boardState,moves,playermoves,AIpieces,playerpieces,treelength+1,nextColor, alpha, beta, score);

                    if(v<nextIter[1])v=nextIter[1];
                    if(alpha<v)alpha=v;
                    if(nextIter.size()>=2){
                        nextIterationScore=nextIter[1];
                        nextIterationIndex=nextIter[0];
                    }
                    if(beta<=alpha){
                        this->resetBoardState(boardState);
                        break;
                        //vector<int> result;
                        //result.push_back(nextIterationIndex);result.push_back(nextIterationScore);result.push_back(i);result.push_back(alpha);result.push_back(beta);
                        //return result;
                    }
                }
                else if(ecolor!=AIcolor){//minimizer
                    score +=setScore;

                    int v = 1000000000;
                    vector<int> nextIter=evaluateMoves(boardState,MoveSet,playermoves,pieceSet,playerpieces,treelength+1,nextColor, alpha, beta, score);
                    //vector<int> nextIter=evaluateMoves(boardState,moves,playermoves,AIpieces,playerpieces,treelength+1,nextColor, alpha, beta, score);

                    if(v>nextIter[1])v=nextIter[1];
                    if(beta>v)beta=v;
                    if(nextIter.size()>=3){
                        nextIterationScore=nextIter[1];
                        nextIterationIndex=nextIter[0];
                    }
                    if(beta<=alpha){
                        this->resetBoardState(boardState);
                        break;
                        //vector<int> result;
                            //result.push_back(nextIterationIndex);result.push_back(nextIterationScore);result.push_back(i);result.push_back(alpha);result.push_back(beta);
                        //return result;
                    }
                }
                //else return {0,0,0};//something went very wrong
            }
            else
                nextIterationScore=score+setScore;
            if(ecolor!=AIcolor && nextIterationScore<movesSetScore)
            {
                movesSetScore=nextIterationScore;
                bestSetIndex=playermoves[i][ii];

            }
            else if(ecolor==AIcolor && nextIterationScore>movesSetScore){
                movesSetScore=nextIterationScore;
                bestSetIndex=moves[i][ii];
            }
            //here we reset the board
            this->resetBoardState(boardState);
        }
        if(AIcolor==ecolor && movesSetScore>highestPieceScore){
            highestPieceScore=movesSetScore;
            bestMoveIndex=bestSetIndex;
            bestPiece = i;
        }
        else if(AIcolor!=ecolor && movesSetScore<highestPieceScore){
            highestPieceScore=movesSetScore;
            bestMoveIndex=bestSetIndex;
            bestPiece = i;
        }
    }
    vector<int> result;
    result.push_back(bestMoveIndex);result.push_back(highestPieceScore);result.push_back(bestPiece);result.push_back(alpha);result.push_back(beta);
    return result;



}
void Checkers::resetBoardState(const string& state){
    for(int i =0; i<64; i++)
        receiveUpdates(state[i],i);
}

string Checkers::describeBoardState(){
    /*
        Makes and returns a string of the same format of those sent over the server in such a way to describe the state of the board.
        This is used by the AI so that is can return to the original board state after making changes while evaluating moves.

    */
    Checkers* temp =checkershead;
    string BoardState="";
    while(temp!=nullptr)
    {
                char piecename = temp->getPieceName();
                //if black piece we send it as uppercase letter
                //if white piece we send it as lowercase letter
                //this is so we can distinquish between the two color sets without
                //needing more than 64 bytes
                if(temp->getPieceColor()==1 && temp->getPieceName()!=' ')
                    piecename=char(int(piecename)+32);
                BoardState+=(piecename);
                temp=temp->nexttile;

    }
    return BoardState;

}
Checkers* Checkers::findPiece(int row, int col){
    /*
        Returns Chess pointer given its row and column numbers.
    */
    Checkers* temp = checkershead;
    if(row<0 || row>7 || col<0 || col>7) return nullptr;
    for(int i=0; i<8; i++)
        for(int ii=0; ii<8;ii++)
        {
            if(temp->getColumn()==col && temp->getRow()==row)
                return temp;
            temp=temp->nexttile;

        }
    return temp;

}
int Checkers::findScore(int destination){
     /*
      * Evaluates move based on whether the destination is advancing it position or if it is capturing a piece. Also the scoring tries to urge pieces to become King if they can.
      */
    int cols = destination%8;
    int rows= destination/8;
    int srcRow = this->getRow();
    int score=0;
    //if(srcRow==rows && cols==this->getColumn()) -1;
    Checkers* des = this->findPiece(rows,cols);
    Checkers* src = this;
    char desType=des->getPieceName();
    char srcType=this->getPieceName();
    bool middleOccupied = checkersboard::tile[(des->getRow()+src->getRow())/2][(des->getColumn()+src->getColumn())/2]->getPiece();
    CheckerPiece p(src->getPieceColor(),src->getPieceName(),src->getRow(),src->getColumn());

    Checkers* middlepiece = checkersboard::tile[(des->getRow()+src->getRow())/2][(des->getColumn()+src->getColumn())/2];
    if(p.checkCapture(des->getRow(), des->getColumn(), middleOccupied, des->getPiece(), middlepiece->getPieceColor()))
        score+=50;
    if(des->row==7 || des->row==0)//about to become a king
        score+=200;

        int randomnumber= rand()%3;
        score+=abs(randomnumber*(srcRow-rows)*2);//we definitely want to encourage advancement. But we also want some randomness in regards to what piece we choose to advance





    //possibly write function to determine if new destination is at higher risk than it is at its current possition
    //factor this into score
    return abs(score);

}
