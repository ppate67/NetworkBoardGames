#include "monopoly.h"
#include "ui_monopoly.h"

monopoly::monopoly(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::monopoly)
{
    ui->setupUi(this);

    connect(ui->pushButton_2, SIGNAL (clicked()), this, SLOT (on_pushButton_2_clicked()));
}

monopoly::~monopoly()
{
    delete ui;
}

/*
click playing monopoly online
*/
void monopoly::on_pushButton_clicked()
{

}

/*
click playing monopoly with AI
*/
void monopoly::on_pushButton_3_clicked()
{

}

/*
click back to main menu
*/
void monopoly::on_pushButton_2_clicked()
{

}
