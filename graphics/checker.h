#ifndef CHECKER_H
#define CHECKER_H

#include <QWidget>
#include <QMainWindow>
#include "mainwindow.h"

namespace Ui {
class mainwindow;
class checker;
}

class checker : public QWidget
{
    Q_OBJECT

public:
    explicit checker(QWidget *parent = 0);
    ~checker();
    QMainWindow *mainwindow;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::checker *ui;
};

#endif // CHECKER_H
