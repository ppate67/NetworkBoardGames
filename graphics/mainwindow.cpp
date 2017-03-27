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

}

/*
click playing chess
*/
void MainWindow::on_pushButton_3_clicked()
{

}

/*
click playing go
*/
void MainWindow::on_pushButton_4_clicked()
{

}

/*
click playing monopoly
*/
void MainWindow::on_pushButton_5_clicked()
{

}

/*
click quiting game
*/
void MainWindow::on_pushButton_6_clicked()
{

}
