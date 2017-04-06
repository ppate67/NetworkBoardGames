#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
    connect(this, SIGNAL (clicked()), this, SLOT (checker::slot1()));
}

/*
click playing chess
*/
void MainWindow::on_pushButton_3_clicked()
{
    connect(this, SIGNAL (clicked()), this, SLOT (chess::slot1()));
}

/*
click playing go
*/
void MainWindow::on_pushButton_4_clicked()
{
    connect(this, SIGNAL (clicked()), this, SLOT (go::slot1()));
}

/*
click playing monopoly
*/
void MainWindow::on_pushButton_5_clicked()
{
    connect(this, SIGNAL (clicked()), this, SLOT (monopoly::slot1()));
}

/*
click quiting game
*/
void MainWindow::on_pushButton_6_clicked()
{
    connect(this, SIGNAL (clicked()), this, SLOT (quit()));
}
