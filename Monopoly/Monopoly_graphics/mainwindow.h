#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "boardspace.h"
#include "player.h"
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
    int turnNumber;
    int numberOfTurns;



public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void on_pushButton_2_clicked();
};

#endif // MAINWINDOW_H
