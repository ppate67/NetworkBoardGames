#ifndef CHESS_H
#define CHESS_H

#include <QWidget>

namespace Ui {
class chess;
}

class chess : public QWidget
{
    Q_OBJECT

public:
    explicit chess(QWidget *parent = 0);
    ~chess();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::chess *ui;
};

#endif // CHESS_H
