#include "players.h"
#include "widget.h"
players::players(QObject *parent) : QObject(parent)
{

}

players::players(QWidget *widget, int color)
{
    process = NULL;
    text_edit_ = NULL;
    play_color_ = color;
    task.append("name\r\n");
    task.append("version\r\n");
}

void players::playMove(QString string)
{
    if (process) {
           if (play_color_ == BLACK) {
               task.append("play white " + string + "\r\n");
               task.append("genmove black\r\n");
           }
           else {
               task.append("play black " + string + "\r\n");
               task.append("genmove white\r\n");
           }
       }
}

void players::playMove(int x, int y, int size)
{
    playMove((x < 0 ? "PASS" :
        QChar('A' + (x < 8 ? x : ++x)) + QString::number(size - y)));
}

players::~players()
{

}
