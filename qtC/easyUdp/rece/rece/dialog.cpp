#include "dialog.h"
#include "ui_dialog.h"

#include <QtNetwork>

QUdpSocket *receiver;

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    //信号槽

    ui->textEdit->setPlainText("datagram");

    receiver = new QUdpSocket(0);
    //receiver->bind(QHostAddress::LocalHost, 6665);
    receiver->bind(QHostAddress::Null, 6665);
    connect(receiver, SIGNAL(readyRead()),this, SLOT(readPendingDatagrams()));



}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::readPendingDatagrams(void)
{
 while (receiver->hasPendingDatagrams()) {
     QByteArray datagram;
     datagram.resize(receiver->pendingDatagramSize());
     receiver->readDatagram(datagram.data(), datagram.size());

     //ui->textEdit->setPlainText(datagram);
     ui->textEdit->append(datagram);
     //数据接收在datagram里
/* readDatagram 函数原型
qint64 readDatagram(char *data,qint64 maxSize,QHostAddress *address=0,quint16 *port=0)
*/
 }
}







