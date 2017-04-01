#include "checkers.h"
#include "pieces.h"

Checkers *temp;
int Checkers::selected=0;

void Checkers::mousePressEvent(QMouseEvent *event)
{
    if(selected==0)
    {
        if (getPiece() == false){
            selected = 0;
        }
        else {
            this->getPieceName();
            this->setStyleSheet("QLabel {background-color:rgb(176, 255, 20);}");
            selected=1;
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
            temp->displayBoard();
        }
        // check piece with ending location to see if move is valid;
        else if (p.checkValid(this->getRow(), this->getColumn(), this->getPieceColor(), this->getPiece()) == true){

            /*if(this->getPieceName() == 'K'){
                exit(1); // a king was captured so the game is over
            }*/

            //Need to put code to check if last piece was captured
            selected=0;
            //this->setTileColor(temp->getTileColor());
            this->setPieceColor(temp->getPieceColor());
            this->setPiece(true);
            this->setpieceName(temp->getPieceName());
            temp->displayBoard();
            this->displayElement(this->getPieceName());
            temp->setPiece(false);
            temp->displayElement(' ');
            temp->displayBoard();
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
        case 'P': this->setPixmap(QPixmap(":/Icons/Red-circle.png"));
            break;
        case 'K': this->setPixmap(QPixmap(":/Icons/lightking.png"));
            break;
        }
    }

    else if(this->piece==true)
    {
        switch(elem)
        {
        case 'P': this->setPixmap(QPixmap(":/Icons/Black-Circle.png"));
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
