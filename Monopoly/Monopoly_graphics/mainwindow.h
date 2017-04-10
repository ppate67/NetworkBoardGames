#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QtGui>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::MainWindow *ui;


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


};

#endif // MAINWINDOW_H
