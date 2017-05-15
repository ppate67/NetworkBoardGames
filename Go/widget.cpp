#include "widget.h"
#include<QtWidgets>
#include <iostream>
#include "players.h"
using namespace std;

widget::widget(QWidget *parent) : QWidget(parent)
{
    setMouseTracking(true);
     setAcceptDrops(true);
     go_game_.reset();
     go_game_.BOARD_KOMI = "7.5";
}

void widget::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::NoButton) {
           point2 = QPoint(-1, -1);
           int distance2 = distance/2;
           int i2, i = x1 - distance2;
           int j2, j = y1 - distance2;
           for (int x = 0; x < go_game_.size; x++) {
               i2 = i + distance;
               if (event->x() > i && event->x() <= i2) {
                   point2.setX(x);
                   break;
              }
               i = i2;
           }
           for (int y = 0; y < go_game_.size; y++) {
               j2 = j + distance;
               if (event->y() > j && event->y() <= j2) {
                   point2.setY(y);
                   break;
               }
               j = j2;
           }
           if ((point1.x() < 0 || point1.y() < 0) &&
               (point2.x() < 0 || point2.y() < 0)) return;
           if (point1 != point2) {
               point1 = point2;
               repaint();
           }
       }
}


void widget::mousePressEvent(QMouseEvent *event)
{
    setFocus();
      if (event->buttons() == Qt::LeftButton && (go_game_.mode & go_game_.turn) && (go_game_.mode & go_game_.tree1.back().turn)) {
          if (point1.x() >= 0 && point1.y() >= 0 && distance > 6) {
              int n = go_game_.tree1.size() - go_game_.index1 - 1;
              if (go_game_.plays(point1.x(), point1.y(), go_game_.turn)) {
                  repaint();
                  if (go_game_.mode != 3) {
                      while (n--) other->task.append("undo\r\n");
                      other->playMove(point1.x(), point1.y(), go_game_.size);
                  }
              }
          }
      }
}

void widget::paintEvent(QPaintEvent *event)
{
       QPainter painter(this);
       distance = min(size().width(),size().height())/(go_game_.size+2);
       cout<<"go_game_.size"<<go_game_.size<<endl;
       cout<<"dist"<<distance<<endl;
       int width;
       width=(go_game_.size - 1)*distance;
        int distance2;
        distance2= distance*2;
        cout<<"dist2"<<distance2<<endl;
        double fonts, r;
        fonts= distance/2.8;
        r = distance*0.4823-0.5869;
        x1 = (size().width() - width)/2;
        y1 = (size().height()-width)/2;
        x2 = x1 + width;
        y2 = y1 + width;
        if (distance>6) {
        painter.setPen(QPen(QColor(48, 48, 48), 0, Qt::SolidLine, Qt::FlatCap));
            for (int i = 0, d = 0; i < go_game_.size; i++, d+=distance) {
                painter.drawLine(x1 + d, y1, x1 + d, y2);
                painter.drawLine(x1, y1 + d, x2 + 1, y1 + d);
            }
            painter.setRenderHint(QPainter::Antialiasing);
           if (show_label_&&fonts >= 6) {
                painter.setPen(Qt::black);
                painter.setFont(QFont("Arial",fonts));
                int k1 = y1 - distance*1.05;
                int k2 = y2 + distance*1.05;
                for (int i = 0, x = x1; i < go_game_.size; i++, x += distance) {
                    QChar value = QChar('A' + i + (i < 8 ? 0 : 1));
                    painter.drawText(x - distance + 1, k1 - distance + 1, distance2, distance2, Qt::AlignCenter, value);
                    painter.drawText(x - distance + 1, k2 - distance + 1, distance2, distance2, Qt::AlignCenter, value);
                }
                k1 = x1 - distance * 1.18;
                k2 = x2 + distance * 1.17;

                for (int i = 0, y = y1; i < go_game_.size; i++, y += distance) {
                    QString value = QString::number(go_game_.size - i);
                    painter.drawText(k1 - distance - 0, y - distance + 1, distance2, distance2, Qt::AlignCenter, value);
                    painter.drawText(k2 - distance - 0, y - distance + 1, distance2, distance2, Qt::AlignCenter, value);
                }
            }
            if (go_game_.size >= 13) {
                painter.setPen(QPen(QColor(15, 15, 15), 1.2, Qt::SolidLine));
                painter.setBrush(Qt::black);

                for (int i = 0, k = 0; i < 9; i++, k += 2) {
                    if (go_game_.size & 1 == 0 && i >= 4) break;
                    painter.drawEllipse(x1 + go_game_.star[k] * distance - 2, y1 + go_game_.star[k + 1] * distance - 2, 5, 5);
                }
            }
            if (r >= 0) {
                for (int j = 0, y = y1; j < go_game_.size; j++, y += distance) {
                    for (int i = 0, x = x1; i < go_game_.size; i++, x += distance) {
                        int color = go_game_.getColor(i, j);
                        int alpha = go_game_.getAlpha(i, j);

                        if (color == BLACK) {
                            painter.setPen(QPen(Qt::black, 1.02, Qt::SolidLine));
                            painter.setBrush(QColor(0, 0, 0, alpha));
                            painter.drawEllipse(QPointF(x + 0.5, y + 0.5), r, r);
                        }
                        else if (color == WHITE) {
                            painter.setPen(QPen(QColor(48, 48, 48), 1.01, Qt::SolidLine));
                            painter.setBrush(QColor(240, 240, 240, alpha));
                            painter.drawEllipse(QPointF(x + 0.5, y + 0.5), r, r);
                        }
                        color = go_game_.areas[j][i];
                        if (color != EMPTY) {
                            painter.setPen(Qt::NoPen);
                            if (color == BLACK) painter.setBrush(QBrush(QColor(0, 0, 0), Qt::BDiagPattern));
                            else painter.setBrush(QBrush(QColor(255, 255, 255), Qt::Dense5Pattern));
                            int half = int (r);
                            int size = half * 2 + 1;
                            painter.drawRect(x - half, y - half, size, size);
                        }
                    }
                }
                int total = go_game_.tree1[go_game_.index1].board.size();
                for (int i = 0; i < total; i++) {
                    gogame::Board board = go_game_.tree1[go_game_.index1].board[i];
                    int color = go_game_.points[board.col][board.row];
                    int x = x1 + board.row * distance;
                    int y = y1 + board.col * distance;

                    if (board.label == gogame::TOKEN_PLAY || board.label == gogame::TOKEN_CIRCLE) {
                        QColor color2 = (color == BLACK ? QColor(240, 240, 240) : Qt::black);
                        int half = double (distance) / 12;

                        painter.setPen(QPen(color2, 1.04, Qt::SolidLine));
                        painter.setBrush(color2);
                        painter.drawEllipse(QPointF(x + 0.5, y + 0.5), half, half);
                    }
                    else if (board.label == gogame::TOKEN_TRIANGLE) {
                        double size = distance / 4.2;
                        double poly[3][2] = {0, -1 * size, 0.866 * size, 0.5 * size, -0.866 * size, 0.5 * size};
                        painter.setPen(QPen(color == BLACK ? Qt::white : Qt::black, 1.2, Qt::SolidLine));
                        painter.drawLine(x + 1 + poly[1][0], y + 1.3 + poly[1][1], x + 1 + poly[2][0], y + 1.3 + poly[2][1]);
                        painter.drawLine(x + 1 + poly[0][0], y + 1.3 + poly[0][1], x + 1 + poly[1][0], y + 1.3 + poly[1][1]);
                        painter.drawLine(x + 1 + poly[0][0], y + 1.3 + poly[0][1], x + 1 + poly[2][0], y + 1.3 + poly[2][1]);
                    }
                    else if (board.label == gogame::TOKEN_MARK) {
                        int size = distance / 4.8;
                        int poly[4][2] = {-1 * size, -1 * size, 1 * size, -1 * size, -1 * size, 1 * size, 1 * size, 1 * size};
                        painter.setPen(QPen(color == BLACK ? Qt::white : Qt::black, 1.2, Qt::SolidLine));
                        painter.drawLine(x + 1 + poly[0][0], y + 1 + poly[0][1], x + 1 + poly[3][0], y + 1 + poly[3][1]);
                        painter.drawLine(x + 1 + poly[1][0], y + 1 + poly[1][1], x + 1 + poly[2][0], y + 1 + poly[2][1]);
                    }
                    else if (board.label == gogame::TOKEN_SQUARE) {
                        int half = distance / 6;
                        int size = half * 2;
                        painter.setPen(QPen(color == BLACK ? QColor(240, 240, 240) : Qt::black, 1, Qt::SolidLine));
                        painter.setRenderHint(QPainter::Antialiasing, false);
                        painter.drawRect(x - half , y - half, size, size);
                        painter.setRenderHint(QPainter::Antialiasing);
                    }
                    else if (board.label == gogame::TOKEN_LABEL || board.label == gogame::TOKEN_NUMBER) {
                        if (fonts >= 6) {
                            if (color == EMPTY) painter.setBackgroundMode(Qt::OpaqueMode);
                            painter.setPen(QPen(color == BLACK ? Qt::white : Qt::black, 1, Qt::SolidLine));
                            painter.setFont(QFont("Arial", fonts));
                            painter.drawText(x - distance + 1, y - distance + 1, distance2, distance2, Qt::AlignCenter,
                                board.label == gogame::TOKEN_LABEL ? QChar(board.value) : QString::number(board.value));
                            if (color == EMPTY) painter.setBackgroundMode(Qt::TransparentMode);
                        }
                    }
                }
                if (!go_game_.BOARD_FILE.isEmpty()) {
                    painter.setPen(Qt::black);
                    painter.setFont(QFont("Arial", 12));
                    painter.drawText(10, 20, go_game_.BOARD_EVENT);
                    painter.drawText(10, 40, go_game_.BOARD_DATE);
                    painter.drawText(10, 60, go_game_.PLAYER_BLACK);
                    painter.drawText(10, 80, go_game_.PLAYER_WHITE);
                    painter.drawText(10, 100, go_game_.BOARD_KOMI);
                    painter.drawText(10, 120, go_game_.BOARD_RESULT);
                }
                if (point1.x() >=0 && point1.y() >= 0) {
                    QColor color = go_game_.index2 >= 0 ? Qt::green : Qt::red;
                    painter.setPen(QPen(color, 2, Qt::SolidLine));
                    painter.setBrush(color);
                    painter.drawEllipse(x1 + point1.x() * distance - 2, y1 + point1.y() * distance - 2, 5, 5);
                }
            }
        }
}

void widget::read(QString file)
{
    if(go_game_.read(file)){
        activateWindow();
        repaint();
        setFocus();
    }
}
