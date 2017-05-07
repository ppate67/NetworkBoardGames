#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QListWidgetItem"
#include "goboard.h"
#include "Checkers1/checkersboard.h"
#include "Chess/chessboard.h"
#include "QTextEdit"
#include  "QVBoxLayout"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void removeplayer();
    static int offline;
    static bool victory;
private slots:
    void on_pushButton_clicked();
    void leaveGo();
    void leaveChess();
    void leaveCheckers();
    void populateList(int size);
    void populateList2(int size);
    void on_pushButton_3_clicked();
    void changeServer();
    void initiateChat();
    void on_pushButton_2_clicked();
     void deleteChat();
    void on_pushButton_5_clicked();
    void on_pushButton_4_clicked();

    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_pushButton_6_clicked();
    void endingScreen(bool victory);
    void on_listWidget_itemActivated(QListWidgetItem *item);
    void on_checkBox_stateChanged(int arg1);


    void on_listWidget_itemChanged(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;
};
class ChatWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ChatWindow(QWidget *parent = 0){

    }
    static void receiveChatMessage(const string & msg);


     QDialog* chatWindow;
     QTextEdit* chatinput;
     QPushButton* button;
     QPushButton* refresh;
     QListWidget *groupBox;
     QVBoxLayout *vbox;
    void setSlots(QWidget *baseWidget);
    public slots:
        void refreshPlayerList();
        void sendChat();


    };
#endif // MAINWINDOW_H
