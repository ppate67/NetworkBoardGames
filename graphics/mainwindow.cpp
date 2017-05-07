#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "chatwindow.h"

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
    connect(this,SIGNAL(goToWidget(int)),this,SLOT(runningWidget(int)));
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
        chessWidget->mainwindow = this;
        goWidget->hide();
        monopolyWidget->hide();
        break;
    case 2:
        this->hide();
        checkerWidget->hide();
        chessWidget->hide();
        goWidget->show();
        goWidget-> mainwindow = this;
        monopolyWidget->hide();
        break;
    case 3:
        this->hide();
        checkerWidget->hide();
        chessWidget->hide();
        goWidget->hide();
        monopolyWidget->show();
        monopolyWidget ->mainwindow = this;
        break;
    }
}
<<<<<<< HEAD
//Chat Window Button, starts client side chat UI and connects to server
void MainWindow::on_pushButton_clicked()
{
     chatwindow chatwindow;
     chatwindow.setModal(true);
     chatwindow.exec();

   /*
  int sockfd, portnum, n;
  struct sockaddr_in serv_addr;
  struct hostent *server;

  char buffer[256];
  portnum = 51717;
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
      error("Error opening socket");

  server = gethostbyname(localhost); //this needs to be the name of whatever machine is running the server, or localhost for you own machine

  if (server == NULL) {

      fprintf(stderr,"Error, no such host\n");
      exit(0);
  }

  bzero((char *) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  bcopy((char *)server->h_addr,
       (char *)&serv_addr.sin_addr.s_addr,
       server->h_length);
  serv_addr.sin_port = htons(portnum);
  //if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
  //    error("Error connecting");
  //printf("Please enter the message: ");
  bzero(buffer,256);
  fgets(buffer,255,stdin);
  n = write(sockfd,buffer,strlen(buffer));
  if (n < 0)
       error("Error writing to socket");
  bzero(buffer,256);
  n = read(sockfd,buffer,255);
  if (n < 0)
       error("Error reading from socket");
  printf("%s\n",buffer);
  close(sockfd);
  */

}
=======

>>>>>>> f2ebf02714879c6badac0e8a909c21dad292a697
