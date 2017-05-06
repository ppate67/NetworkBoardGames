#ifndef MONOPOLYBOARD_H
#define MONOPOLYBOARD_H
#include "boardspace.h"
#include "player.h"
#include "cards.h"
#include <QMainWindow>
#include <QtGui>
#include <iostream>
using namespace std;

namespace Ui {
class monopolyboard;
}

class monopolyboard : public QMainWindow
{
    Q_OBJECT
private:
    Ui::monopolyboard *ui;
    boardSpace** spaces;
    Player** players;
    Card** CommunityChest;
    Card** Chance;
    int turnNumber;
    int numberOfTurns;



public:
    explicit monopolyboard(QWidget *parent = 0);
    ~monopolyboard();


private slots:
    void on_pushButton_2_clicked();
    //void on_Test_Button_clicked();
};

#endif // MONOPOLYBOARD_H
