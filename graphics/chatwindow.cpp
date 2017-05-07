#include "chatwindow.h"
#include "ui_chatwindow.h"
#include <unistd.h>

extern int sockfd;
extern char buffer;

chatwindow::chatwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chatwindow)
{
    ui->setupUi(this);
}

chatwindow::~chatwindow()
{
    delete ui;
}

void chatwindow::on_pushButton_clicked()
{

}
