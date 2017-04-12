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
                sendGameMsg();
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
            sendGameMsg();
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
                    sendGameMsg();
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
void Checkers::displayElement(char elem)
{
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
    while(1){
        if(pnt->prevtile==NULL)
            return pnt;
        pnt=pnt->prevtile;
    }
}
void Checkers::fillArray(Checkers* tiles[8][8],Checkers* pnt){
    tiles[0][0]=pnt;
    for(int ii=0;ii<8;ii++){
        for(int i=0;i<8;i++){
            tiles[i][ii]=pnt;
            pnt=pnt->nexttile;
        }

    }

}
void Checkers::receiveUpdates(char piece1, int iteration){
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
    Checkers::checkersturn=1;
}

