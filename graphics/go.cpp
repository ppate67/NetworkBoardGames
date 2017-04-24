#include "go.h"
#include "ui_go.h"

go::go(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::go)
{
    ui->setupUi(this);

    connect(ui->pushButton_2, SIGNAL (clicked()), this, SLOT (on_pushButton_2_clicked()));
}

go::~go()
{
    delete ui;
}

/*
click playing go online
*/
void go::on_pushButton_clicked()
{

}

/*
click playing go with AI
*/
void go::on_pushButton_3_clicked()
{

}

/*
click back to main menu
*/
void go::on_pushButton_2_clicked()
{

}
