#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Display the board
    QPixmap board(":/board.png");
    ui->label->setPixmap(board.scaled(551,551,Qt::KeepAspectRatio));

    //Quit Button
    connect(ui->pushButton, SIGNAL (clicked()), QApplication::instance(), SLOT(quit()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
