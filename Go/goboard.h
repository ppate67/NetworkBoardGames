#ifndef GOBOARD_H
#define GOBOARD_H
#include "QWidget"
#include "go.h"

class GoBoard
{

public:
    GoBoard();

    void display(QWidget *baseWidget,Go *tile[13][13]);
    void forfeitclose();
    void removeplayer();
    static void updateScores();
//    ~GoBoard(){
////        Go* temp=Go::head;
////        while(temp!=nullptr){
////            Go* deltemp=temp;
////            temp=temp->nexttile;
////            delete[] deltemp;
////        }


//    }

};

#endif // GOBOARD_H
