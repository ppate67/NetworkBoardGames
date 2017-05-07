#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "checker.h"
#include "chess.h"
#include "go.h"
#include "monopoly.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void goToWidget(int);

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void runningWidget(int);


    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    checker *checkerWidget;
    chess *chessWidget;
    go *goWidget;
    monopoly *monopolyWidget;

};

#endif // MAINWINDOW_H
