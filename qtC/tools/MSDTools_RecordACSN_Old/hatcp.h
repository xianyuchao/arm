#ifndef HATCP_H
#define HATCP_H

#include <QObject>
#include<QString>
#include<QTcpSocket>
#include<QTimer>


#include <QtNetwork>


#include "globalDefine.h"

#define HA_DISCONNECTED 0;
#define HA_CONNECTED 1;

class HATcp : public QObject
{
    Q_OBJECT
public:
    explicit HATcp(QObject *parent = 0);
    ~HATcp();
    void startConnect(QString add,QString port);
    bool sendDate(QVector<unsigned char> block);
    QVector<unsigned char> getDate();
    bool getConnectState();
    void closeConnection();
    void closeConnectionUnusual();

    QByteArray getudpdatagram(void);

signals:
    void tcpArrived();     //接收到一条报文
    void haveConnected();  //连接成功
    void connectHaveClosed(); //连接关闭
    void error(int); //错误信息错误
    /* 0： 未知错误
     * 1： 无法连接
     * 2： 报文长度与数据内标识长度不一致
     * 3:  包长度错误
     * 5:  连接丢失*/
    void  udpArrived();     //接收到一条报文

public slots:
    void connectReady();
    void setConnectFlagFalse();
    void connectionClosedByServer();
    void connectError();
    void update();

    void readPendingDatagrams();// UDP接收槽,处理


private:
    QTcpSocket haTcp;
    bool connectFlag;
    QVector<unsigned char> receiveBlock;

    QString connectedIP;
    QString connectedPort;

    QUdpSocket *receiver;
    QByteArray datagram;
};

#endif // HATCP_H
