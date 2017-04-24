#include "chess.h"
#include <QtGui>
#include "QMessageBox"
#include "Chess/pieces.h"

Chess *temp;
Chess* Chess::chesshead=NULL;
int Chess::chessturn=1;
int Chess::playercolor=0;
int Chess::selected=0;
int Chess::offline=0;

<<<<<<< HEAD


=======
>>>>>>> 3bb0b83979e2555235b131b8ddca9899693e4366
void Chess::mousePressEvent(QMouseEvent *event)
{
    if(selected==0)
    {
        if ((getPiece() == false || this->getPieceColor()!=Chess::playercolor)|| chessturn==0){
            selected = 0;
        }
        else {
            this->getPieceName();
            this->setStyleSheet("QLabel {background-color:rgb(176, 255, 20);}");
            selected=1;
            chessboard::drawpath(this);
            temp=this;
        }
    }
    else
    {
        // give selected color, name, row, and column to piece object
        Piece p(temp->getPieceColor(), temp->getPieceName(), temp->getRow(), temp->getColumn());
        // clicked back on itself so allow a new choice
        if (this->getTileNum() == temp->getTileNum()){
            selected = 0;
            chessboard::erasepath();
            temp->displayBoard();
        }
        // check piece with ending location to see if move is valid;
        else if (p.checkValid(this->getRow(), this->getColumn(), this->getPieceColor(), this->getPiece()) == true ){
            p.setRow(this->getRow());
            p.setCol(this->getColumn());
            if(this->getPieceName() == 'K'){
                if (this->getPieceColor() == 0){
                    Piece::bkr = this->getRow();
                    Piece::bkc = this->getColumn();
                }
                else {
                    Piece::wkr = this->getRow();
                    Piece::wkc = this->getColumn();
                }
                chessboard::erasepath();
                //this->setTileColor(temp->getTileColor());
                this->setPieceColor(temp->getPieceColor());
                this->setPiece(true);
                this->setpieceName(temp->getPieceName());
                temp->displayBoard();
                this->displayElement(this->getPieceName());
                temp->setPiece(false);
                temp->displayElement(' ');
                temp->setpieceName(' ');
                temp->displayBoard();
                if(offline==0)
                    sendGameMsg();

                else
                    passToAI();
                //exit(1); // a king was captured so the game is over<--no good because it exits out of the console as well which is undesired

            }
            selected=0;
            chessboard::erasepath();
            //this->setTileColor(temp->getTileColor());
            this->setPieceColor(temp->getPieceColor());
            this->setPiece(true);
            this->setpieceName(temp->getPieceName());
            temp->displayBoard();
            this->displayElement(this->getPieceName());
            temp->setPiece(false);
            temp->displayElement(' ');
            temp->setpieceName(' ');
            temp->displayBoard();
            if (temp->getPieceColor() == 0){ // black piece was just moved, check if it put white king in check
                if(p.checkValid(Piece::wkr, Piece::wkc, 1, true) == true){
                    if(chessboard::checkMate()==true)
                        cout << "Game Over" << endl; // possibly add gif later
                    else
                        cout << "White piece in check" << endl; // just testing now, should add pop up later
                }
            }
            else{ // white piece was jsut moved, check if it put black king in check
                if(p.checkValid(Piece::bkr, Piece::bkc, 1, true) == true){
                    if(chessboard::checkMate()==true)
                        cout << "Game Over" << endl; // possibly add gif later
                    else
                        cout << "Black piece in check" << endl; // just testing now, should add pop up later
                }
            }
            if(this->getPieceName()=='P' && this->getPieceColor()==0 && this->getRow()==7){
                pawnPromotion(this);

            }
            else if(this->getPieceName()=='P' && this->getPieceColor()==1 && this->getRow()==0){
                pawnPromotion(this);

            }
            else
                if(offline==0)
                    sendGameMsg();
                else
                    passToAI();
        }


    }
}

void Chess::displayElement(char elem)
{
    this->pieceName=elem;

    if(this->pieceColor==1 && this->piece==true)
    {
        switch(elem)
        {
        case 'P': this->setPixmap(QPixmap(":/Icons/lightpawn.png"));
            break;
        case 'R': this->setPixmap(QPixmap(":/Icons/lightrook.png"));
            break;
        case 'H': this->setPixmap(QPixmap(":/Icons/lightknight.png"));
            break;
        case 'K': this->setPixmap(QPixmap(":/Icons/lightking.png"));
            break;
        case 'Q': this->setPixmap(QPixmap(":/Icons/lightqueen.png"));
            break;
        case 'B': this->setPixmap(QPixmap(":/Icons/lightbishop.png"));
            break;
        }
    }

    else if(this->piece==true)
    {
        switch(elem)
        {
        case 'P': this->setPixmap(QPixmap(":/Icons/darkpawn.png"));
            break;
        case 'R': this->setPixmap(QPixmap(":/Icons/darkrook.png"));
            break;
        case 'H': this->setPixmap(QPixmap(":/Icons/darkknight.png"));
            break;
        case 'K': this->setPixmap(QPixmap(":/Icons/darkking.png"));
            break;
        case 'Q': this->setPixmap(QPixmap(":/Icons/darkqueen.png"));
            break;
        case 'B': this->setPixmap(QPixmap(":/Icons/darkbishop.png"));
            break;
        }
    }
    else
        this->clear();
}

void Chess::displayBoard()
{
    if(this->tileColor==1)
    {
        this->setStyleSheet("QLabel {background-color:rgb(255, 193, 122);}:hover{background-color: rgb(62, 139, 178);}");
    }
    else
    {
        this->setStyleSheet("QLabel {background-color:rgb(147, 91, 26);}:hover{background-color: rgb(62, 139, 178);}");
    }
}



void Chess::sendGameMsg(){
    QByteArray BufferPing;
    int des=0;
    int vecsize=GameManager::games.size();
    for(int i =0; i<vecsize; i++){
        int playsize=GameManager::games[i].size();
        for(int ii=0; ii<playsize;ii++){
            if(GameManager::games[i][ii][2]==GameManager::clientID)
                des=i;
        }
    }
    BufferPing.append(char(des));
    BufferPing.append(char(1));//type =1 for chess games
    Chess*tiles[8][8];
    Chess*pnt=findHead(this);
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
    Chess::chessturn=0;
}
Chess* Chess::findHead(Chess* pnt){
    while(1){
        if(pnt->prevtile==NULL)
            return pnt;
        pnt=pnt->prevtile;
    }
}
void Chess::fillArray(Chess* tiles[8][8],Chess* pnt){
    tiles[0][0]=pnt;
    for(int ii=0;ii<8;ii++){
        for(int i=0;i<8;i++){
            tiles[i][ii]=pnt;
            pnt=pnt->nexttile;
        }

    }

}
void Chess::receiveUpdates(char piece1, int iteration){
    Chess*temp=Chess::chesshead;
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
                Chess::chessturn=1;
        }
    }

}
void Chess::pawnPromotion(Chess *pawn){//makes window for players to choose what to promote to
    QDialog *promotion = new QDialog;
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();
    int height = screenGeometry.height();
    int width = screenGeometry.width();
    promotion->setGeometry(width/2-300,height/2-175,600,350);
    promotion->setWindowFlags(Qt::WindowStaysOnTopHint);
    promotion->setAttribute(Qt::WA_TranslucentBackground, true);

    promotion->setWindowFlags(Qt::Popup | Qt::FramelessWindowHint);
    promotion->setStyleSheet("background:transparent;");
    ChessOptions *queen = new ChessOptions(promotion);
    ChessOptions *bishop = new ChessOptions(promotion);
    ChessOptions *rook = new ChessOptions(promotion);
    ChessOptions *knight = new ChessOptions(promotion);
    queen->setGeometry(20,100,120,120);
    bishop->setGeometry(170,100,120,120);
    rook->setGeometry(320,100,120,120);
    knight->setGeometry(470,100,120,120);
    queen->setScaledContents(true);
    bishop->setScaledContents(true);
    rook->setScaledContents(true);
    knight->setScaledContents(true);
    queen->setStyleSheet("QLabel {background-color:rgb(255, 255, 255);}:hover{background-color: rgb(62, 139, 178);}");
    bishop->setStyleSheet("QLabel {background-color:rgb(255, 255, 255);}:hover{background-color: rgb(62, 139, 178);}");
    rook->setStyleSheet("QLabel {background-color:rgb(255, 255, 255);}:hover{background-color: rgb(62, 139, 178);}");
    knight->setStyleSheet("QLabel {background-color:rgb(255, 255, 255);}:hover{background-color: rgb(62, 139, 178);}");
    queen->piecetype=0; bishop->piecetype=1; rook->piecetype=2; knight->piecetype=3;
    if(playercolor==1){
        queen->setPixmap(QPixmap(":/Icons/lightqueen.png"));
        bishop->setPixmap(QPixmap(":/Icons/lightbishop.png"));
        rook->setPixmap(QPixmap(":/Icons/lightrook.png"));
        knight->setPixmap(QPixmap(":/Icons/lightknight.png"));

    }
    else{
        queen->setPixmap(QPixmap(":/Icons/darkqueen.png"));
        bishop->setPixmap(QPixmap(":/Icons/darkbishop.png"));
        rook->setPixmap(QPixmap(":/Icons/darkrook.png"));
        knight->setPixmap(QPixmap(":/Icons/darkknight.png"));

    }
    promotion->show();
    queen->pawn=pawn;
    bishop->pawn=pawn;
    rook->pawn=pawn;
    knight->pawn=pawn;
    queen->window=promotion;
    bishop->window=promotion;
    rook->window=promotion;
    knight->window=promotion;

}
void ChessOptions::mousePressEvent(QMouseEvent *event){
    if(this->piecetype==0){
        this->pawn->setpieceName('Q');
        this->pawn->displayElement(this->pawn->getPieceName());

    }
    else if(this->piecetype==1){
        this->pawn->setpieceName('B');
        this->pawn->displayElement(this->pawn->getPieceName());

    }
    else if(this->piecetype==2){
        this->pawn->setpieceName('R');
        this->pawn->displayElement(this->pawn->getPieceName());

    }
    else if(this->piecetype==3){
        this->pawn->setpieceName('H');
        this->pawn->displayElement(this->pawn->getPieceName());

    }
    this->pawn->sendGameMsg();
    this->window->close();
}

void Chess::passToAI(){
    int AIcolor = 0; if(playercolor==0) AIcolor=1;
    //make a list of pieces that can make moves and use that list with the
    //possible moves functions for chess
    Chess* temp = chesshead;
    vector<Chess*> posspieces;
    vector<Chess*> playerpieces;
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
            Piece p(AIcolor,temp->getPieceName(),row,col);
            vector<int> possibleMoves;

            for(int i =0; i<8; i++)
            {
                for(int ii =0; ii<8; ii++){
                    if(i==row && ii==col);//possibleMoves.push_back(i*8+ii);
                    else{
                        Chess *targetDes = this->findPiece(i,ii);
                        bool validity=p.checkValid(i,ii,targetDes->getPieceColor(),targetDes->getPiece());
                        if(validity)
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
            Piece p(playercolor,temp->getPieceName(),row,col);
            vector<int> possibleMoves;

            for(int i =0; i<8; i++)
            {
                for(int ii =0; ii<8; ii++){
                    if(i==row && ii==col);//possibleMoves.push_back(i*8+ii);
                    else{
                        Chess *targetDes = this->findPiece(i,ii);
                        bool validity=p.checkValid(i,ii,targetDes->getPieceColor(),targetDes->getPiece());
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
    Chess* bestPiece= posspieces[0];
    if(bestMove[2]<posspieces.size())
        bestPiece = posspieces[bestMove[2]];
    Chess *bestDes = findPiece(des/8,des%8);
    bestPiece->setPiece(false);
    bestDes->setpieceName(bestPiece->getPieceName());
    bestDes->setPiece(true);
    bestPiece->setPieceColor(2);
    bestDes->setPieceColor(AIcolor);
    bestPiece->setpieceName(' ');
    bestPiece->displayElement(' ');

    bestDes->displayElement(bestDes->getPieceName());

}
//we will attempt to make moves by looking 5 moves into the future. We must then simulate opponent moves as if they were playing at the AI's skill level
vector<int> Chess::evaluateMoves(const string& originalBoardState,vector<vector<int>> moves,vector<vector<int>> playermoves, vector<Chess*> AIpieces,vector<Chess*> playerpieces, int treelength, int ecolor, int alpha, int beta, int score){//returns index of best move and the score of that move. treelength is how far in the future we are evaluating to
//    QMessageBox::information(
//            new QMessageBox(),
//            "Debug Window",
//            QString::fromStdString("debugout"));//debuging purposes delete




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

                Chess* newposs;
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
                vector<Chess*> pieceSet;

                Chess* temp = chesshead;
                if(treelength<1){
                    vector<Chess*>temppieces;
                    if(AIcolor==nextColor)temppieces=AIpieces;
                    else temppieces=playerpieces;
                    //temppieces[i]=newposs;
                    for(auto temp : temppieces){//while(temp!=nullptr){
                        vector<int>possibleMoves;
                        //possibleMoves=temp->findPossMoves();
                        Piece p(nextColor,temp->getPieceName(),temp->getRow(),temp->getColumn());
                        for(int j =0; j<8; j++)
                        {
                            for(int jj =0; jj<8; jj++){

                                if(j==row && jj==col);//possibleMoves.push_back(j*8+jj);
                                else{
                                    if(temp->getPieceColor()==nextColor){
                                        Chess *targetDes = this->findPiece(j,jj);
                                        bool validity=p.checkValid(j,jj,targetDes->getPieceColor(),targetDes->getPiece());
                                        if(validity)
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

int Chess::findScore(int destination){
    int cols = destination%8;
    int rows= destination/8;
    int srcRow = this->getRow();
    int score=0;
    //if(srcRow==rows && cols==this->getColumn()) -1;
    Chess* des = this->findPiece(rows,cols);
    char desType=des->getPieceName();
    char srcType=this->getPieceName();

    switch(desType){
    case 'P':
        score+=5*rows;//capturing pawns closer to AI's side of the board is more valuable.
        break;
    case 'K':
        score+=1000000;//as to nearly guarentee this being the choosen path
        break;
    case 'Q':
        score+=5000;
        break;
    case'H':
        score+=100;
        break;
    case 'B':
        score+=100;
        break;
    case 'R':
        score+=175;
        break;
    case ' '://case in which the destination is not occupied.
        int randomnumber= rand()%3;
        score+=abs(randomnumber*(srcRow-rows)*2);//we definitely want to encourage advancement. But we also want some randomness in regards to what piece we choose to advance
        break;



    }
    //possibly write function to determine if new destination is at higher risk than it is at its current possition
    //factor this into score
    return abs(score);
}
Chess* Chess::findPiece(int row, int col){
    Chess* temp = chesshead;
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
string Chess::describeBoardState(){

    Chess* temp =chesshead;
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
void Chess::resetBoardState(const string& state){
    for(int i =0; i<64; i++)
        receiveUpdates(state[i],i);
}
vector<int> Chess::findPossMoves(){//this function was written in an attempt to optimize the AI. It was a failure and is currently hidden from the repository since it was ~800 lines of code and would be a waste of space.
    //what is currently here is a placeholder
    vector<int> result;
    return result;
       }


