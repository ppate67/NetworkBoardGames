#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Display the board
    QPixmap board(":/board.jpg");
    ui->label->setPixmap(board.scaled(551,551,Qt::KeepAspectRatio));

    //Quit Button
    connect(ui->pushButton, SIGNAL (clicked()), QApplication::instance(), SLOT(quit()));

    //Roll Dice
    //connect(ui-> pushButton_2, SIGNAL (clicked()), QApplication::instance(), getProperty)
}

MainWindow::~MainWindow()
{
    delete ui;
}
