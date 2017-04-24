#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    connect(ui->pushButton_2, SIGNAL (clicked()), this, SLOT (on_pushButton_2_clicked()));
    connect(ui->pushButton_3, SIGNAL (clicked()), this, SLOT (on_pushButton_3_clicked()));
    connect(ui->pushButton_4, SIGNAL (clicked()), this, SLOT (on_pushButton_4_clicked()));
    connect(ui->pushButton_5, SIGNAL (clicked()), this, SLOT (on_pushButton_5_clicked()));
    //click quiting game
    connect(ui->pushButton_6, SIGNAL (clicked()), this, SLOT (on_pushButton_6_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
click playing checker
*/
void MainWindow::on_pushButton_2_clicked()
{
    emit goToWidget(0);
}

/*
click playing chess
*/
void MainWindow::on_pushButton_3_clicked()
{
    emit goToWidget(1);
}

/*
click playing go
*/
void MainWindow::on_pushButton_4_clicked()
{
    emit goToWidget(2);
}

/*
click playing monopoly
*/
void MainWindow::on_pushButton_5_clicked()
{
    emit goToWidget(3);
}

void MainWindow::on_pushButton_6_clicked()
{
    QApplication* app;
    app->exit(0);
}
//show widget
void MainWindow::runningWidget(int widgetNum)
{
    switch(widgetNum)
    {
    case 0:
        this->hide();
        checkerWidget->show();
        checkerWidget->mainwindow = this;
        chessWidget->hide();
        goWidget->hide();
        monopolyWidget->hide();
        break;
    case 1:
        this->hide();
        checkerWidget->hide();
        chessWidget->show();
        goWidget->hide();
        monopolyWidget->hide();
        break;
    case 2:
        this->hide();
        checkerWidget->hide();
        chessWidget->hide();
        goWidget->show();
        monopolyWidget->hide();
        break;
    case 3:
        this->hide();
        checkerWidget->hide();
        chessWidget->hide();
        goWidget->hide();
        monopolyWidget->show();
        break;
    }
}

