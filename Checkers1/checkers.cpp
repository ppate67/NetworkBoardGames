#include "Checkers1/pieces2.h"

Checkers *temp2;
int Checkers::selected=0;
Checkers* Checkers::checkershead=NULL;
int Checkers::checkersturn=1;
int Checkers::playercolor=0;
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
        }
        // check piece with ending location to see if move is valid;
        else if (p.checkValid2(this->getRow(), this->getColumn(), this->getPieceColor(), this->getPiece()) == true){

            /*if(this->getPieceName() == 'K'){
                exit(1); // a king was captured so the game is over
            }*/

            //Need to put code to check if last piece was captured
            selected=0;
            //this->setTileColor(temp2->getTileColor());
            this->setPieceColor(temp2->getPieceColor());
            this->setPiece(true);
            this->setpieceName(temp2->getPieceName());
            temp2->displayBoard();
            this->displayElement(this->getPieceName());
            temp2->setPiece(false);
            temp2->displayElement(' ');
            temp2->displayBoard();
            sendGameMsg();
        }
    }
}

void Checkers::displayElement(char elem)
{
    this->pieceName=elem;
    this->setScaledContents(true);
    if(this->pieceColor==1 && this->piece==true)
    {
        switch(elem)
        {
        case 'K': this->setPixmap(QPixmap(":/Icons/lightking.png"));
            break;
        case 'P': this->setPixmap(QPixmap(":/Icons/Red-circle.png"));
            break;

        }
    }

    else if(this->piece==true)
    {
        switch(elem)
        {
        case 'P': this->setPixmap(QPixmap(":/checkers/Black-Circle.png"));
            break;
        case 'K': this->setPixmap(QPixmap(":/Icons/darkking.png"));
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
void Checkers::capturePiece(){}
void Checkers::checkCapture(){}

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

