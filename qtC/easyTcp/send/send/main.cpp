#include "dialog.h"
#include <QApplication>
#include <QtNetwork>

QTcpSocket *client;

void sendTCP(void)
{

    char *data=(char*)"hello qt!";
    client = new QTcpSocket(0);
    client->connectToHost(QHostAddress("127.0.0.1"), 6665);
    //client->connectToHost(QHostAddress("192.168.1.105"), 6665);
    //client->connectToHost(QHostAddress::Any, 6665);
    client->write(data);

}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w;
    w.show();



    return a.exec();
}
