#ifndef PLAYERS_H
#define PLAYERS_H

#include <QObject>

#include <QProcess>

class QTextEdit;

// the class of players

class players : public QObject
{
    Q_OBJECT
public:
    explicit players(QObject *parent = 0);
    players(QWidget *parent, int color);
    void playMove(QString string);
    void playMove(int x, int y, int size);
    ~players();
    players *other;
    QTextEdit *text_edit_;
    QStringList task;

signals:
public slots:
private:
    QProcess *process;
   int play_color_;

};

#endif // PLAYERS_H
