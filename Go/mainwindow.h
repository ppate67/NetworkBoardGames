#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QListWidgetItem"
#include "goboard.h"
#include "Checkers1/checkersboard.h"
#include "Chess/chessboard.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void removeplayer();
private slots:
    void on_pushButton_clicked();
    void leaveGo();
    void leaveChess();
    void leaveCheckers();
    void populateList(int size);
    void populateList2(int size);
    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_5_clicked();
    void on_pushButton_4_clicked();

    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_pushButton_6_clicked();

    void on_listWidget_itemActivated(QListWidgetItem *item);
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
