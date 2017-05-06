#ifndef CHECKER_H
#define CHECKER_H

#include <QWidget>
#include <QMainWindow>

namespace Ui {
class checker;
}

class checker : public QWidget
{
    Q_OBJECT

public:
    explicit checker(QWidget *parent = 0);
    ~checker();
    QMainWindow *mainwindow;
    //CheckerolWindow *checkerolwindow
    //CheckeraiWindow *checkeraiwindow

signals:
    void goToWidget(int);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void runningWidget(int);


private:
    Ui::checker *ui;
};

#endif // CHECKER_H
