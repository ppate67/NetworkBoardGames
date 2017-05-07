#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "boardspace.h"
#include "player.h"
#include "cards.h"
#include <QMainWindow>
#include <QtGui>
#include <iostream>
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::MainWindow *ui;
    boardSpace** spaces;
    Player** players;
    Card** CommunityChest;
    Card** Chance;
    int turnNumber;
    int numberOfTurns;



public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void on_pushButton_2_clicked();
   // void on_pushButton_3_clicked();
    //void on_pushButton_4_clicked();
};
#endif // MAINWINDOW_H
