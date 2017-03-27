#ifndef CHECKER_H
#define CHECKER_H

#include <QWidget>

namespace Ui {
class checker;
}

class checker : public QWidget
{
    Q_OBJECT

public:
    explicit checker(QWidget *parent = 0);
    ~checker();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::checker *ui;
};

#endif // CHECKER_H
