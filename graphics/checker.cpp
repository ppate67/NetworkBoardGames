#include "checker.h"
#include "ui_checker.h"

checker::checker(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::checker)
{
    ui->setupUi(this);

    connect(ui->pushButton_2, SIGNAL (clicked()), this, SLOT (on_pushButton_2_clicked()));
    connect(ui->pushButton_3, SIGNAL (clicked()), this, SLOT (on_pushButton_3_clicked()));
    connect(ui->pushButton, SIGNAL (clicked()), this, SLOT (on_pushButton_clicked()));
    connect(this,SIGNAL(goToWidget(int)),this,SLOT(runningWidget(int)));
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
    emit goToWidget(0);
}

/*
click playing checker with AI
*/
void checker::on_pushButton_3_clicked()
{
    emit goToWidget(1);
}

/*
click back to main menu
*/
void checker::on_pushButton_2_clicked()
{
    this->hide();
    mainwindow->show();
}

void MainWindow::runningWidget(int widgetNum)
{
    switch(widgetNum)
    {
    case 0:
        this->hide();
        //checkerolwindow->show();
        //checkeraiwindow->hide();
        break;
    case 1:
        this->hide();
        //checkerolwindow->hide();
        //checkeraiwindow->show();
        break;
    }
}
