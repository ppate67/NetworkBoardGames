#include "goboard.h"
//Go *temp;
Go* Go::head=NULL;
int Go::turn=1;
int Go::color=0;
int Go::opponentScore=0;
int Go::playerScore=0;
int Go::wterr=0;
int Go::blterr=0;
void Go::mousePressEvent(QMouseEvent *event)
{
    if(turn==0 || !checkPositionValidity(this->getColumn(),this->getRow(),this->getPieceColor()))
    {
		//checks if position is valid to place stone on

    }
    else
    {
		//if position is valid then a stone is placed with a color equal to the player's color.
		//a player can only place a stone with their color.
		//board is then updated and a message is sent to server so that the other player can 
		//update their board
        this->setPieceColor(color);
        this->setPiece(true);
        updateEntireBoard();
        this->displayElement(' ');
        sendGameMsg();
        this->displayBoard(this->type);
    }
}
int Go::getUserColor(){
	//this method would allow for a user to find out what their color is. 
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
    
    Go* temp=Go::head;
    vector<Go*> tempcontainer;
    blterr=0;wterr=0;
    while(temp!=nullptr){
        vector<Go*> positions;
        if(temp->checkLiberties(temp,temp,&positions)<=0){
            tempcontainer.push_back(temp);
        }

        positions.clear();
        if(temp->getPieceColor()==2){

              if(temp->calculateTerritory(temp,temp,&positions,1)>0)
                      blterr++;

        }
        positions.clear();
        if(temp->getPieceColor()==2){
               if(temp->calculateTerritory(temp,temp,&positions,0)>0)
                    wterr++;

        }
        positions.clear();
        temp=temp->nexttile;
    }

    for(int i=0; i<tempcontainer.size(); i++){
        if(tempcontainer[i]->getPieceColor()!=Go::color && tempcontainer[i]->getPieceColor()!=2)
            Go::playerScore++;
        else if(tempcontainer[i]->getPieceColor()!=2)
            Go::opponentScore++;
        tempcontainer[i]->setPieceColor(2);
        tempcontainer[i]->setPiece(false);


    }
    temp=Go::head;
    while(temp!=nullptr){
        temp->displayElement(' ');
        temp->displayBoard(temp->type);
        temp=temp->nexttile;
    }
    GoBoard::updateScores();

}
void Go::displayElement(char elem)
{
	//displays picture of stone based on the color assigned to the tile
	//userColor is a misnomer it should be called tilecolor - this change will be made shortly
    if(this->userColor==1 && this->piece==true)
    {
        this->setPixmap(QPixmap(":/Icons2/blackstone.png"));
        this->setScaledContents(true);
    }

    else if(this->piece==true)
    {
        this->setPixmap(QPixmap(":/Icons2/whitestone.png"));
        this->setScaledContents(true);
    }
    else
        this->clear();
    }
void Go::displayBoard(int type)
{
	//this sets up the coloring of the board.
	//also displays the crosses and line segments needed to make the board look the way it does
    switch(type){
        case 0:
            this->setStyleSheet("QLabel {background-color:rgb(147, 91, 26);image:url(:/Icons2/circlecross.png);}:hover{background-color: rgb(62, 139, 178);}");
            break;
        case 1:
            this->setStyleSheet("QLabel {background-color:rgb(147, 91, 26);image:url(:/Icons2/CROSS.png);}:hover{background-color: rgb(62, 139, 178);}");
            break;
        case 2:
            this->setStyleSheet("QLabel {background-color:rgb(147, 91, 26);image:url(:/Icons2/bottomside.png);}:hover{background-color: rgb(62, 139, 178);}");
            break;
        case 3:
            this->setStyleSheet("QLabel {background-color:rgb(147, 91, 26);image:url(:/Icons2/topside.png);}:hover{background-color: rgb(62, 139, 178);}");
            break;
        case 4:
            this->setStyleSheet("QLabel {background-color:rgb(147, 91, 26);image:url(:/Icons2/leftside.png);}:hover{background-color: rgb(62, 139, 178);}");
            break;
        case 5:
            this->setStyleSheet("QLabel {background-color:rgb(147, 91, 26);image:url(:/Icons2/rightside.png);}:hover{background-color: rgb(62, 139, 178);}");
            break;
        case 6:
            this->setStyleSheet("QLabel {background-color:rgb(147, 91, 26);image:url(:/Icons2/bottomleft.png);}:hover{background-color: rgb(62, 139, 178);}");
            break;
        case 7:
            this->setStyleSheet("QLabel {background-color:rgb(147, 91, 26);image:url(:/Icons2/topleft.png);}:hover{background-color: rgb(62, 139, 178);}");
            break;
        case 8:
            this->setStyleSheet("QLabel {background-color:rgb(147, 91, 26);image:url(:/Icons2/bottomright.png);}:hover{background-color: rgb(62, 139, 178);}");
            break;
        case 9:
            this->setStyleSheet("QLabel {background-color:rgb(147, 91, 26);image:url(:/Icons2/topright.png);}:hover{background-color: rgb(62, 139, 178);}");
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


    return liberties;
}
//bool korule(GoBoard board){}

//isConnected no longer needed as it has been made obselete by just using a vector in the checkLiberties method
//It very likely will become useful for calculating final scores of the game however.
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
	//sends message to server containing information needed to describe the entire state of the Go game
	//for Go this simply entails sending the color value of each tile
    QByteArray BufferPing;
    int des=0;
    int vecsize=GameManager::games.size();
    for(int i =0; i<vecsize; i++){
        int playsize=GameManager::games[i].size();
        for(int ii=0; ii<playsize;ii++){
            if(GameManager::games[i][ii][2]==GameManager::clientID && GameManager::games[i][ii][0]==0)
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
	//finds head of Go data structures
	//used when contructing game message
    while(1){
        if(pnt->prevtile==NULL)
            return pnt;
        pnt=pnt->prevtile;
    }
}
void Go::fillArray(Go* tiles[13][13],Go* pnt){
	//fills array of go objects so that they can be easily iterated through
    tiles[0][0]=pnt;
    for(int ii=0;ii<13;ii++){
        for(int i=0;i<13;i++){
            tiles[i][ii]=pnt;
            pnt=pnt->nexttile;
        }

    }

}
void Go::receiveUpdates(int color, int iteration){
	//this static method is iteratively called by the client class
	//it takes the color value from inside a tcp message and uses it to update the go board
	//iteration is used as an index of which tile on the board to update.
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

int Go::calculateTerritory(Go* position, Go* prevposition, vector<Go*>* positions, int tercolor){
    int anticolor =0; if (tercolor==0)anticolor++;
    for(int i=0; i<positions->size(); i++)
        if(positions->at(i)==position)
            return -1;
    if(position->getPieceColor()==2)
        positions->push_back(position);
    if(position->getPieceColor()==anticolor)
        return 0;
    //if(position==originalpos && position !=prevposition)
      //  return 0;
    int terrs=1;

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
        if(below->getPieceColor()==anticolor)
            return 0;
        if(below->getPieceColor()==2 && below!=prevposition)
            {
                if(calculateTerritory(below,position,positions,tercolor)!=0){
                    if(calculateTerritory(below,position,positions,tercolor)==-1)
                        terrs++;
                    terrs+=calculateTerritory(below,position,positions,tercolor);
                }
                else
                    return 0;

        }
        if(below->getPieceColor()==tercolor)
            terrs++;
    }
    if(above!=nullptr){
        if(above->getPieceColor()==anticolor)
            return 0;
        if(above->getPieceColor()==2 && above!=prevposition)
           {
            if(calculateTerritory(above,position,positions,tercolor)!=0){
                if(calculateTerritory(above,position,positions,tercolor)==-1)
                    terrs++;
                terrs+=calculateTerritory(above,position,positions,tercolor);
            }
            else
                return 0;


            }
        if(above->getPieceColor()==tercolor)
            terrs++;
    }
    if(right!=nullptr){
        if(right->getPieceColor()==anticolor)
            return 0;
        if(right->getPieceColor()==2 && right!=prevposition)
             {
            if(calculateTerritory(right,position,positions,tercolor)!=0){
                if(calculateTerritory(right,position,positions,tercolor)==-1)
                    terrs++;
                terrs+=calculateTerritory(right,position,positions,tercolor);
            }
            else
                return 0;

            }
        if(right->getPieceColor()==tercolor)
            terrs++;
    }
    if(left!=nullptr){
        if(left->getPieceColor()==anticolor)
            return 0;
        if(left->getPieceColor()==2 && left!=prevposition)
        {
            if(calculateTerritory(left,position,positions,tercolor)!=0){
                if(calculateTerritory(left,position,positions,tercolor)==-1)
                    terrs++;
                terrs+=calculateTerritory(left,position,positions,tercolor);
            }
            else
                return 0;


        }
        if(left->getPieceColor()==tercolor)
            terrs++;
    }


    return terrs;


}
