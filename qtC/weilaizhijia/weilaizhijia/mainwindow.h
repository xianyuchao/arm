#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "testlib.h"
#include <QtNetwork>

namespace Ui {
class MainWindow;
}



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QUdpSocket *sender;
#define TARGETHOST "115.28.93.201 " // 向该主机ip发送udp包
#define TARGETHOSTPORT  7001

#define DEVICEID    "1287370388"    // 设备号  1
#define DEVPASSWORD "1234567890"    // 密码

#define DEVICEID2    "1287370402"    // 设备号  2

    //const char *devs[]={"1287370388","1287370402"};
    QStringList longerList ;

    QString device; // 服务器返回的设备号
    QString account;
    QString servertime;//服务器返回时间
    QString command;

    //发送心跳包：f=1&d=1287370388&m=1234567890&z=XXX&from=sb->server
    //服务器返回：f=1&d=1287370388&t=2015-07-29 09:27:15&from=server->sb

    void heartbreak(float state);

    //接收服务器控制：f=a&d=1287370388&n=brother0952&com=open&from=server->sb
    //回复服务器（不是必须）：f=b&d=1287370388&m=1234567890&n=brother0952&com=XXXXXX&from=sb->server
    //服务器返回：f=b&d=1287370388&n=brother0952&from=server->sb
    void cmdback(float state);

    //上传数据：f=d&d=1287370388&m=1234567890&num=223&c=1&&a=11&from=sb->server
    //返回f=d&d=1287370388&from=server->sb
    QString getcmd(QString str);// 接收控制命令

    //A设备控制B设备
    //f=e&d=1287370388&m=1234567890&d1=1287370402&m1=1234567890&com=open&from=sb->server
    //服务器返回：f=e&d=1287370388&from=server->sb
    //B会接收：f=f&d=1287370388&com=open&from=sb->server
    //      m=server->sb

    //打洞,d1 主动,d 被动设备
    //主动：f=4&d1=1287370388&m1=1234567890&d=1287370402&m=1234567890&from=sb->server
    //主动接收到服务器：f=4&d1=1287370388&from=server->sb

    //被动接收到服务器：f=5&d1=1287370388&ip=119.145.137.54:17852&from=server->sb
    //          rom=server->mobile


    void sendUDP(QByteArray datagram);
    QTimer      m_timer;

private slots:
    void timeout();
    void readPendingDatagrams();
    void on_pushButton_clicked();
};

#endif // MAINWINDOW_H
