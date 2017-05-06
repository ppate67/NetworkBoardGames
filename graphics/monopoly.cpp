#include "monopoly.h"
#include "ui_monopoly.h"

monopoly::monopoly(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::monopoly)
{
    ui->setupUi(this);

    connect(ui->pushButton_2, SIGNAL (clicked()), this, SLOT (on_pushButton_2_clicked()));
    connect(ui->pushButton_3, SIGNAL (clicked()), this, SLOT (on_pushButton_3_clicked()));
    connect(ui->pushButton, SIGNAL (clicked()), this, SLOT (on_pushButton_clicked()));
    connect(this,SIGNAL(goToWidget(int)),this,SLOT(runningWidget(int)));
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
    emit goToWidget(0);
}

/*
click playing monopoly with AI
*/
void monopoly::on_pushButton_3_clicked()
{
    emit goToWidget(1);
}

/*
click back to main menu
*/
void monopoly::on_pushButton_2_clicked()
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
        //monopolyolwindow->show();
        //monopoluaiwindow->hide();
        break;
    case 1:
        this->hide();
        //monopolyolwindow->hide();
        //monopolyaiwindow->show();
        break;
    }
}
