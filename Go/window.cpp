#include <QApplication>
#include <QtWidgets>

#include "window.h"

// set the gui
BoardView::BoardView(QWidget *parent) : QWidget(parent)
{
    setStyleSheet("background-color: rgb(0, 205, 205);");
    setMouseTracking(true);
    setAcceptDrops(true);

    board.Reset();
    board.BOARD_KOMI = "7.5";
}

// read files
void BoardView::Read(QString file)
{
    if (board.Read(file)) {
        activateWindow();
        repaint();
        setFocus();
    }
}

// press event
void BoardView::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Right || event->key() == Qt::Key_Down) {
        if (board.NextNode()) repaint();
    }
    else if (event->key() == Qt::Key_Left || event->key() == Qt::Key_Up) {
        if (board.PrevNode()) repaint();
    }
    else if (event->key() == Qt::Key_Home) {
        if (board.FirstNode()) repaint();
    }
    else if (event->key() == Qt::Key_End) {
        if (board.LastNode()) repaint();
    }
    else if (event->key() == Qt::Key_PageUp) {
        if (board.PrevNode(10)) repaint();
    }
    else if (event->key() == Qt::Key_PageDown) {
        if (board.NextNode(10)) repaint();
    }
    else if (event->key() == Qt::Key_Space) {
        ShowLabel = ! ShowLabel;
        repaint();
    }
    else if (event->key() == Qt::Key_Escape) {
        if (board.Index2 >= 0) {
            while (board.Index2 >= 0)
                board.PrevNode();
            repaint();
        }
    }
    else if (event->key() == Qt::Key_S) {
        board.BOARD_FILE = "001.SGF";
        if (board.Write(board.BOARD_FILE)) board.BOARD_FILE.clear();
        else repaint();
    }
    else if (event->key() == Qt::Key_P) { // pass
        if ((board.Mode & board.Turn) && (board.Mode & board.Tree.back().Turn)) {
            board.Play(-1, -1, board.Turn);
            repaint();
            if (board.Mode != 3)
                Other->PlayMove(-1, -1, 0);
        }
    }
}


// drag event
void BoardView::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls() && board.Mode == 3)
        event->accept();
}

// drop event
void BoardView::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasUrls())
        Read(event->mimeData()->urls().at(0).toLocalFile());
}

// wheel event
void BoardView::wheelEvent(QWheelEvent *event)
{
    if (event->delta() < 0) {
        if (board.NextNode()) repaint();
    }
    else if (event->delta() > 0) {
        if (board.PrevNode()) repaint();
    }
}

 // move event
void BoardView::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::NoButton) {
        Cursor2 = QPoint(-1, -1);

        int Dist2 = Dist / 2;
        int i2, i = x1 - Dist2;
        int j2, j = y1 - Dist2;

        for (int x = 0; x < board.Size; x++) {
            i2 = i + Dist;
            if (event->x() > i && event->x() <= i2) {
                Cursor2.setX(x);
                break;
            }
            i = i2;
        }

        for (int y = 0; y < board.Size; y++) {
            j2 = j + Dist;
            if (event->y() > j && event->y() <= j2) {
                Cursor2.setY(y);
                break;
            }
            j = j2;
        }

        if ((Cursor.x() < 0 || Cursor.y() < 0) &&
            (Cursor2.x() < 0 || Cursor2.y() < 0)) return;

        if (Cursor != Cursor2) {
            Cursor = Cursor2;
            repaint();
        }
    }
}

void BoardView::mousePressEvent(QMouseEvent *event)
{
    setFocus();

    if (event->buttons() == Qt::LeftButton && (board.Mode & board.Turn) && (board.Mode & board.Tree.back().Turn)) {
        if (Cursor.x() >= 0 && Cursor.y() >= 0 && Dist > 6) {
            int n = board.Tree.size() - board.Index - 1;
            if (board.Play(Cursor.x(), Cursor.y(), board.Turn)) {
                repaint();
                if (board.Mode != 3) {
                    while (n--) Other->Task.append("undo\r\n");
                    Other->PlayMove(Cursor.x(), Cursor.y(), board.Size);
                }
            }
        }
    }
}
