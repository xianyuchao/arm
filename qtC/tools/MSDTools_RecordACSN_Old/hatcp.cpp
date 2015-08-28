#include "hatcp.h"

#include <QDebug>
#include "widget.h"

HATcp::HATcp(QObject *parent) :
    QObject(parent)
{
    receiver = new QUdpSocket(0);
    receiver->bind(QHostAddress::Null, 7083);
    connect(receiver, SIGNAL(readyRead()),this, SLOT(readPendingDatagrams()));


    connectFlag = false;
    connect(&haTcp,SIGNAL(connected()),this,SLOT(connectReady()));
    connect(&haTcp,SIGNAL(readyRead()),this,SLOT(update()));
    connect(&haTcp,SIGNAL(disconnected()),this,SLOT(connectionClosedByServer()));
    connect(&haTcp,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(connectError()));
}

HATcp::~HATcp()
{

}

void HATcp::startConnect(QString add,QString port)
{
    haTcp.connectToHost(add,(quint16)port.toInt(0,10));
    if(!haTcp.waitForConnected(1000))
    {
        connectError();
    }
    else
    {
        connectedIP = add;
        connectedPort = port;
    }
}

bool HATcp::sendDate(QVector<unsigned char> block)
{
    if(connectFlag == true)
    {
        QByteArray sendBlock;
        quint8 temp;
        QDataStream out(&sendBlock,QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_2);
        foreach (temp, block) {
            out << temp;
        }
        haTcp.write(sendBlock);
        return true;
    }
    else
    {
        return false;
    }
}

QVector<unsigned char> HATcp::getDate()
{
    //qDebug()<<receiveBlock.isEmpty()<<endl;
    return receiveBlock;
}

bool HATcp::getConnectState()
{
    return connectFlag;
}

void HATcp::closeConnection()
{
    connectFlag = false;
    haTcp.close();
}

void HATcp::connectReady()
{
    connectFlag = true;
    haTcp.setSocketOption(QAbstractSocket::KeepAliveOption,	QVariant(1));
    qDebug()<<"tcpMode1:"<<haTcp.socketOption(QAbstractSocket::KeepAliveOption);
    emit haveConnected();
}

void HATcp::setConnectFlagFalse()
{
    connectFlag = false;
}

void HATcp::connectionClosedByServer()
{
    qDebug()<<"connectionClosedByServer:"<<connectFlag<<endl;
    if(connectFlag == true)
    {
        emit error(5);
    }
    emit connectHaveClosed();
}

void HATcp::connectError()
{
    haTcp.close();
    qDebug()<<"connectError"<<endl;
    if(connectFlag == false)
    {
        emit error(1);  //连接失败
    }
    else
    {
        emit error(5); //连接丢失
        connectFlag = false;
    }
}

void HATcp::update()
{
    return;
}

void HATcp::readPendingDatagrams(void)
{
    while (receiver->hasPendingDatagrams())
    {
        datagram.resize(receiver->pendingDatagramSize());
        receiver->readDatagram(datagram.data(), datagram.size());
        emit udpArrived();

        //qDebug()<<datagram;
    }
}

QByteArray HATcp::getudpdatagram(void)
{
    return datagram;
}
