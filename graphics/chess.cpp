#include "chess.h"
#include "ui_chess.h"

chess::chess(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::chess)
{
    ui->setupUi(this);

    connect(ui->pushButton_2, SIGNAL (clicked()), this, SLOT (on_pushButton_2_clicked()));
    connect(ui->pushButton_3, SIGNAL (clicked()), this, SLOT (on_pushButton_3_clicked()));
    connect(ui->pushButton, SIGNAL (clicked()), this, SLOT (on_pushButton_clicked()));
    connect(this,SIGNAL(goToWidget(int)),this,SLOT(runningWidget(int)));

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
    emit goToWidget(0);
}

/*
click playing chess with AI
*/
void chess::on_pushButton_3_clicked()
{
    emit goToWidget(1);
}

/*
click back to main menu
*/
void chess::on_pushButton_2_clicked()
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
        //chessolwindow->show();
        //chessaiwindow->hide();
        break;
    case 1:
        this->hide();
        //chessolwindow->hide();
        //chessaiwindow->show();
        break;
    }
}
