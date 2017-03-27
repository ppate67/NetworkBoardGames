#include <Qchatwindow>
#include <QTcpSocket>

#include "ui_chatwindow.h"

class chatwindow : public Qchatwindow, public Ui::chatwindow
{
    Q_OBJECT

    public:

        chatwindow(QWidget *parent=0);

    private slots:

        void on_loginButton_clicked();

        void on_sayButton_clicked();

        void readyRead();

        void connected();

    private:
        QTcpSocket *socket;
};
