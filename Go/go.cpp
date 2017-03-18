#include "go.h"

Go *temp;
Go* Go::head=NULL;
int Go::turn=1;
int Go::color=0;
void Go::mousePressEvent(QMouseEvent *event)
{
    if(turn==0 || !checkPositionValidity(this->getColumn(),this->getRow(),this->getPieceColor()))
    {

        //this->setStyleSheet("QLabel {background-color:rgb(176, 255, 20);}");

        //temp=this;
    }
    else
    {
        //turn=0;
        //this->setTileColor(temp->getTileColor());

        this->setPieceColor(color);
        this->setPiece(true);
        updateEntireBoard();
        this->displayElement(' ');
        sendGameMsg();
        this->displayBoard(this->type);
    }
}
int Go::getUserColor(){

    int vecsize=GameManager::games.size();
    for(int i=0; i<vecsize; i++){
        int playsize= GameManager::games[i].size();
        int counter=0;
        for(int ii=0; ii<playsize; ii++){
            if(GameManager::games[i][ii][2]==GameManager::clientID && GameManager::games[i][ii][1]==1){
                if(counter>0)return 1;
                else return 1;
            }
            if(GameManager::games[i][ii][1]==1) counter++;
        }
    }


}
void Go::updateEntireBoard(){
    //purpose is to updata tiles that have been affected by a change in liberties
    //currently crashes the program sometimes?
    Go* temp=Go::head;
    vector<Go*> tempcontainer;
    while(temp!=nullptr){
        vector<Go*> positions;
        if(temp->checkLiberties(temp,temp,&positions)<=0){
            tempcontainer.push_back(temp);
        }
        temp=temp->nexttile;
        positions.clear();
    }
    for(int i=0; i<tempcontainer.size(); i++){
        tempcontainer[i]->setPieceColor(2);
        tempcontainer[i]->setPiece(false);
    }
    temp=Go::head;
    while(temp!=nullptr){
        temp->displayElement(' ');
        temp->displayBoard(temp->type);
        temp=temp->nexttile;
    }

}
void Go::displayElement(char elem)
{

    if(this->userColor==1 && this->piece==true)
    {
        this->setPixmap(QPixmap(":/Icons/Icons/blackstone.png"));
        this->setScaledContents(true);
    }

    else if(this->piece==true)
    {
        this->setPixmap(QPixmap(":/Icons/Icons/whitestone.png"));
        this->setScaledContents(true);
    }
    else
        this->clear();
    }
void Go::displayBoard(int type)
{
    switch(type){
        case 0:
            this->setStyleSheet("QLabel {background-color:rgb(147, 91, 26);image:url(:/Icons/Icons/circlecross.png);}:hover{background-color: rgb(62, 139, 178);}");
            break;
        case 1:
            this->setStyleSheet("QLabel {background-color:rgb(147, 91, 26);image:url(:/Icons/Icons/CROSS.png);}:hover{background-color: rgb(62, 139, 178);}");
            break;
        case 2:
            this->setStyleSheet("QLabel {background-color:rgb(147, 91, 26);image:url(:/Icons/Icons/bottomside.png);}:hover{background-color: rgb(62, 139, 178);}");
            break;
        case 3:
            this->setStyleSheet("QLabel {background-color:rgb(147, 91, 26);image:url(:/Icons/Icons/topside.png);}:hover{background-color: rgb(62, 139, 178);}");
            break;
        case 4:
            this->setStyleSheet("QLabel {background-color:rgb(147, 91, 26);image:url(:/Icons/Icons/leftside.png);}:hover{background-color: rgb(62, 139, 178);}");
            break;
        case 5:
            this->setStyleSheet("QLabel {background-color:rgb(147, 91, 26);image:url(:/Icons/Icons/rightside.png);}:hover{background-color: rgb(62, 139, 178);}");
            break;
        case 6:
            this->setStyleSheet("QLabel {background-color:rgb(147, 91, 26);image:url(:/Icons/Icons/bottomleft.png);}:hover{background-color: rgb(62, 139, 178);}");
            break;
        case 7:
            this->setStyleSheet("QLabel {background-color:rgb(147, 91, 26);image:url(:/Icons/Icons/topleft.png);}:hover{background-color: rgb(62, 139, 178);}");
            break;
        case 8:
            this->setStyleSheet("QLabel {background-color:rgb(147, 91, 26);image:url(:/Icons/Icons/bottomright.png);}:hover{background-color: rgb(62, 139, 178);}");
            break;
        case 9:
            this->setStyleSheet("QLabel {background-color:rgb(147, 91, 26);image:url(:/Icons/Icons/topright.png);}:hover{background-color: rgb(62, 139, 178);}");
            break;

        }
}
int Go::checkLiberties(Go* position, Go* prevposition, vector<Go*>* positions){
    //need to check for ring structures as they will lead to the program crashing
    //ring structures can start at originalpos or any other arbitrary connected stone
    //this is a problem as it requires a semi complicated method to check for rings.
    //normally in a linked list checking for rings is trivial but this is data-based
    //rings
    //a method for this would be too time consuming so it'd be better to just have a vector of
    //pointers and see if we have checked a position before with the vector.
    //consumes more memory but takes less time and is less complex (which are more important in this application)

    for(int i=0; i<positions->size(); i++)
        if(positions->at(i)==position)
            return 0;
    positions->push_back(position);
    if(position->getPieceColor()==2)
        return 0;
    //if(position==originalpos && position !=prevposition)
      //  return 0;
    int liberties=0;
    Go* above = nullptr;
    Go* below = nullptr;
    Go* right = nullptr;
    Go* left = nullptr;
    Go* temp =position;
    Go* temp2 = position;
    for(int i =0; i<13; i++){
        if(temp!=nullptr)
            temp=temp->prevtile;
        if(temp2!=nullptr)
            temp2 = temp2->nexttile;
        if(i==0 && temp!=nullptr && temp->getRow()<12){
            left = temp;
        }
        if(i==12 && temp!=nullptr)
            above = temp;
        if(i==0 && temp2!=nullptr && temp2->getRow()>0)
            right = temp2;
        if(i==12 && temp2!=nullptr)
            below = temp2;
    }
    if(below!=nullptr){
        if(below->getPieceColor()==2)
            liberties++;
        else if(below->getPieceColor()==position->getPieceColor() && below!=prevposition)
            liberties+=checkLiberties(below,position,positions);
    }
    if(above!=nullptr){
        if(above->getPieceColor()==2)
            liberties++;
        else if(above->getPieceColor()==position->getPieceColor() && above!=prevposition)
            liberties+=checkLiberties(above,position,positions);
    }
    if(right!=nullptr){
        if(right->getPieceColor()==2)
            liberties++;
        else if(right->getPieceColor()==position->getPieceColor() && right!=prevposition)
            liberties+=checkLiberties(right,position,positions);
    }
    if(left!=nullptr){
        if(left->getPieceColor()==2)
            liberties++;
        else if(left->getPieceColor()==position->getPieceColor() && left!=prevposition)
            liberties+=checkLiberties(left,position,positions);
    }





    //need to get rid of doubley counted liberties
    //we can define a isConnected method to check if two arbitry stones are connected
    //we can subtract one from the liberties counter if
    //they are connected, share a liberty, and the current stone being "investigated"
    // is on the left or below the liberty (so we only decrement once)
//    Go* twoabove=above;
//    if(above!=nullptr){
//        for(int i=0; i<13; i++)
//        {
//            twoabove=twoabove->prevtile;
//            if(twoabove==nullptr)
//                break;
//        }
//    }
//    if(right->nexttile!=nullptr)
//    if(isConnected(position,position,right->nexttile) && right->getPieceColor()==2){
//        liberties--;
//    }
//    if(twoabove!=nullptr)
//    if(isConnected(position,position,twoabove) && above->getPieceColor()==2){
//        liberties--;
//    }
    return liberties;
}
//bool korule(GoBoard board){}
bool Go::isConnected(Go* curposition,Go* prevpos, Go* otherposition){
    //first call curposition = temp and otherposition = the position we are checking if curposition is connected to
    //so we want to recursively go from curposition to otherposition
    //if it ever returns true that will cause it to return true for parent calls
    //returns true if curposition==otherposition and
    bool result=false;
    Go* above = nullptr;
    Go* below = nullptr;
    Go* right = nullptr;
    Go* left = nullptr;
    Go* temp1 =curposition;
    Go* temp2 = curposition;
    //need way to ensure we don't go in circles
    //this will be done by having an original Go* that
    //we compare against and return false if we stumble across it

    for(int i =0; i<13; i++){
        if(temp1!=nullptr)
            temp1=temp1->prevtile;
        if(temp2!=nullptr)
            temp2 = temp2->nexttile;

        if(i==0 && temp1!=nullptr && temp1!=prevpos && temp1->getRow()<12 && temp1->getPieceColor()==prevpos->getPieceColor()){
            left = temp1;
        }
        if(i==12 && temp1!=nullptr && temp1!=prevpos && temp1->getPieceColor()==prevpos->getPieceColor())
            above = temp1;
        if(i==0 && temp2!=nullptr && temp2!=prevpos && temp2->getRow()>0 && temp2->getPieceColor()==prevpos->getPieceColor())
            right = temp2;
        if(i==12 && temp2!=nullptr && temp2!=prevpos && temp2->getPieceColor()==prevpos->getPieceColor())
            below = temp2;
    }
    if(curposition==otherposition)
        return true;
    if(above==nullptr && below==nullptr && left==nullptr && right==nullptr)
        return false;

    if(above!=nullptr && above->getPieceColor()==prevpos->getPieceColor()){
        if(isConnected(above,curposition, otherposition))
            result =true;
    }
    if(below!=nullptr && below->getPieceColor()==prevpos->getPieceColor()){//second condition redundant
        if(isConnected(below,curposition, otherposition))
            result=true;
    }
    if(left!=nullptr && left->getPieceColor()==prevpos->getPieceColor()){
        if(isConnected(left,curposition, otherposition))
            result=true;
    }
    if(left!=nullptr && left->getPieceColor()==prevpos->getPieceColor()){
        if(isConnected(right,curposition, otherposition))
            result=true;
    }
    return result;
}
//bool suicide(GoBoard board){}
bool Go::checkPositionValidity(int corx, int cory, int color){
    //needs to be done
    return true;

}
bool Go::placeStone(int corx, int cory){return true;}
void Go::captureStones(){}
void Go::addStonePoints(int numcapstones, int playercolor){}
void Go::sendGameMsg(){
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
    BufferPing.append(char(0));
    Go*tiles[13][13];
    Go*pnt=findHead(this);
    fillArray(tiles,findHead(this));

    for(int j=0; j<13;j++){
        for(int i=0;i<13;i++){
            BufferPing.append(char(tiles[i][j]->getPieceColor()));

        }
    }

    Client::s->write(BufferPing);
    Client::s->flush();
    Go::turn=0;
}
Go* Go::findHead(Go* pnt){
    while(1){
        if(pnt->prevtile==NULL)
            return pnt;
        pnt=pnt->prevtile;
    }
}
void Go::fillArray(Go* tiles[13][13],Go* pnt){
    tiles[0][0]=pnt;
    for(int ii=0;ii<13;ii++){
        for(int i=0;i<13;i++){
            tiles[i][ii]=pnt;
            pnt=pnt->nexttile;
        }

    }

}
void Go::receiveUpdates(int color, int iteration){
    Go*temp=Go::head;
    for(int i=0;i<iteration;i++){
        temp=temp->nexttile;
    }
    temp->setPieceColor(color);
    if(temp->getPieceColor()!=2)
        temp->setPiece(true);
    else
        temp->setPiece(false);

    temp->displayElement(' ');
    temp->displayBoard(temp->type);
    Go::turn=1;
}

