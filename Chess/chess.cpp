#include "chess.h"

Chess *temp;

int Chess::selected=0;
void Chess::mousePressEvent(QMouseEvent *event)
{
    if(selected==0)
    {
        this->getPieceName();
        this->setStyleSheet("QLabel {background-color:rgb(176, 255, 20);}");
        selected=1;
        temp=this;
    }
    else
    {
        selected=0;
        //this->setTileColor(temp->getTileColor());
        this->setPieceColor(temp->getPieceColor());
        this->setPiece(true);
        this->setpieceName(temp->getPieceName());
        temp->displayBoard();
        this->displayElement(this->getPieceName());
        temp->piece=false;
        temp->displayElement(' ');
        temp->displayBoard();
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
