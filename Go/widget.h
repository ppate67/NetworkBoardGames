#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "gogame.h"

class players;

//the widget class
class widget : public QWidget
{
    Q_OBJECT
public:
    explicit widget(QWidget *parent = 0);

    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    void read(QString file);
    gogame go_game_;
    int distance;
signals:
private:
    int x1, y1, x2, y2;
    int show_label_ = 0;
    int show_text_ = 0;
    players *other;
    QPoint point1 = QPoint(-1, -1);
    QPoint point2 = QPoint(-1, -1);
public slots:
};

#endif // WIDGET_H
