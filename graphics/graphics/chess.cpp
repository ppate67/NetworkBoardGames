#include "chess.h"
#include "ui_chess.h"

chess::chess(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::chess)
{
    ui->setupUi(this);
}

chess::~chess()
{
    delete ui;
}

/*
click playing chess online
*/
void chess::on_pushButton_clicked()
{

}

/*
click playing chess with AI
*/
void chess::on_pushButton_3_clicked()
{

}

/*
click back to main menu
*/
void chess::on_pushButton_2_clicked()
{
    connect(this, SIGNAL (clicked()), this, SLOT (mainwindow::slot1()));
}
