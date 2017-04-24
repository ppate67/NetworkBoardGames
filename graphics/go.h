#ifndef GO_H
#define GO_H

#include <QWidget>
#include <QMainWindow>


namespace Ui {
class go;
}

class go : public QWidget
{
    Q_OBJECT

public:
    explicit go(QWidget *parent = 0);
    ~go();
    QMainWindow *mainwindow;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::go *ui;
};

#endif // GO_H
