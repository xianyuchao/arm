#include "dialog.h"
#include <QApplication>
#include <QtNetwork>


void sendUDP(void)
{

    QUdpSocket *sender;
    sender = new QUdpSocket(0);
    QByteArray datagram = "hello world!";
    //UDP广播
    sender->writeDatagram(datagram.data(),datagram.size(),QHostAddress::Broadcast,6665);
    //向特定IP发送
    //QHostAddress serverAddress = QHostAddress("255.255.255.255");//4个255也是广播，，和上面功能一样

    //QHostAddress serverAddress = QHostAddress("127.0.0.1");
   // sender->writeDatagram(datagram.data(), datagram.size(),serverAddress, 6665);
    /* writeDatagram函数原型，发送成功返回字节数，否则-1
    qint64 writeDatagram(const char *data,qint64 size,const QHostAddress &address,quint16 port)
    qint64 writeDatagram(const QByteArray &datagram,const QHostAddress &host,quint16 port)
    */
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w;
    w.show();



    return a.exec();
}
