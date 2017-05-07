#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <unistd.h>
#include <QDialog>

namespace Ui {
class chatwindow;
}

class chatwindow : public QDialog
{
    Q_OBJECT

public:
    explicit chatwindow(QWidget *parent = 0);
    ~chatwindow();

private slots:
    void on_pushButton_clicked();

    void on_lineEdit_editingFinished();

private:
    Ui::chatwindow *ui;
};

#endif // CHATWINDOW_H
