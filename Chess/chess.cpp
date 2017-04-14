#include "chess.h"
#include <QtGui>
#include "QMessageBox"
#include "Chess/pieces.h"

Chess *temp;
Chess* Chess::chesshead=NULL;
int Chess::chessturn=1;
int Chess::playercolor=0;
int Chess::selected=0;

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
            if(this->getPieceName() == 'K'){
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
                sendGameMsg();
                exit(1); // a king was captured so the game is over
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
            if(this->getPieceName()=='P' && this->getPieceColor()==0 && this->getRow()==7){
                pawnPromotion(this);

            }
            else if(this->getPieceName()=='P' && this->getPieceColor()==1 && this->getRow()==0){
                pawnPromotion(this);

            }
            else
                sendGameMsg();
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

