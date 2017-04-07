#include "checker.h"
#include "ui_checker.h"

checker::checker(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::checker)
{
    ui->setupUi(this);
}

checker::~checker()
{
    delete ui;
}

/*
click playing checker online
*/
void checker::on_pushButton_clicked()
{

}

/*
click playing checker with AI
*/
void checker::on_pushButton_3_clicked()
{

}

/*
click back to main menu
*/
void checker::on_pushButton_2_clicked()
{
    connect(this, SIGNAL (clicked()), this, SLOT (mainwindow::slot1()));
}
