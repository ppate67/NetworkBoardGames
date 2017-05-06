#ifndef CHESS_H
#define CHESS_H

#include <QWidget>
#include <QMainWindow>


namespace Ui {
class chess;
}

class chess : public QWidget
{
    Q_OBJECT

public:
    explicit chess(QWidget *parent = 0);
    ~chess();
    QMainWindow *mainwindow;
    //ChessolWindow *chessolwindow
    //ChessaiWindow *chessaiwindow

signals:
    void goToWidget(int);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void runningWidget(int);


private:
    Ui::chess *ui;
};

#endif // CHESS_H
