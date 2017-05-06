#include "go.h"
#include "ui_go.h"

go::go(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::go)
{
    ui->setupUi(this);

    connect(ui->pushButton_2, SIGNAL (clicked()), this, SLOT (on_pushButton_2_clicked()));
    connect(ui->pushButton_3, SIGNAL (clicked()), this, SLOT (on_pushButton_3_clicked()));
    connect(ui->pushButton, SIGNAL (clicked()), this, SLOT (on_pushButton_clicked()));
    connect(this,SIGNAL(goToWidget(int)),this,SLOT(runningWidget(int)));
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
    emit goToWidget(0);
}
}

/*
click playing go with AI
*/
void go::on_pushButton_3_clicked()
{
    emit goToWidget(1);
}

/*
click back to main menu
*/
void go::on_pushButton_2_clicked()
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
        //goolwindow->show();
        //goaiwindow->hide();
        break;
    case 1:
        this->hide();
        //goolwindow->hide();
        //goaiwindow->show();
        break;
    }
}
