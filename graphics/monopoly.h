#ifndef MONOPOLY_H
#define MONOPOLY_H

#include <QWidget>
#include <QMainWindow>


namespace Ui {
class monopoly;
}

class monopoly : public QWidget
{
    Q_OBJECT

public:
    explicit monopoly(QWidget *parent = 0);
    ~monopoly();
    QMainWindow *mainwindow;
    //MonolopyolWindow *monopolyolwindow
    //MonolopyaiWindow *monopolyaiwindow

signals:
    void goToWidget(int);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void runningWidget(int);


private:
    Ui::monopoly *ui;
};

#endif // MONOPOLY_H
