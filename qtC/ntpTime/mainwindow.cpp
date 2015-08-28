#include "mainwindow.h"
#include "ui_mainwindow.h"




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    GetNetworkTime(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}




QDateTime MainWindow::GetNetworkTime(char* time_str)
{

    //利用ntp服务器获取网络时间
    QUdpSocket udp_sock;
    udp_sock.connectToHost("time.windows.com",123);
    //发送请求时间的请求
    qint8 LI = 0;
    qint8 VN = 3;
    qint8 MODE = 3;
    qint8 STRATUM = 0;
    qint8 POLL = 4;
    qint8 PREC = -6;
    QDateTime epoch(QDate(1900, 1, 1));
    qint32 second = quint32(epoch.secsTo(QDateTime::currentDateTime()));
    qint32 temp = 0;
    QByteArray time_req(48, 0);
    time_req[0] = (LI <<6) | (VN <<3) | (MODE);
    time_req[1] = STRATUM;
    time_req[2] = POLL;
    time_req[3] = PREC & 0xff;
    time_req[5] = 1;
    time_req[9] = 1;
    time_req[40] = (temp=(second&0xff000000)>>24);
    temp = 0;
    time_req[41]=(temp=(second&0x00ff0000)>>16);
    temp = 0;
    time_req[42] = (temp=(second&0x0000ff00)>>8);
    temp = 0;
    time_req[43] = ((second&0x000000ff));

    QDateTime cur_dt;
    //阻塞等待连接成功
    if(udp_sock.waitForConnected(60000))
    {

        udp_sock.flush();
        //发送时间请求
        udp_sock.write(time_req);
        udp_sock.flush();

        //阻塞等待消息返回
        if(udp_sock.waitForReadyRead(120000))
        {

            QByteArray new_time;
            QDateTime epoch(QDate(1900, 1, 1));
            QDateTime unix_start(QDate(1970, 1, 1));
            while(udp_sock.hasPendingDatagrams())
            {

                new_time.resize(udp_sock.pendingDatagramSize());
                udp_sock.read(new_time.data(), new_time.size());

}
            QByteArray TransmitTimeStamp ;
            TransmitTimeStamp = new_time.right(8);
            quint32 seconds=TransmitTimeStamp[0];
            quint8 temp=0;
            for(int j=1;j<=3;j++)
            {

                seconds=seconds<<8;
                temp=TransmitTimeStamp[j];
                seconds=seconds+temp;

}

            cur_dt.setTime_t(seconds- epoch.secsTo(unix_start));

}
        else
        {

            cur_dt = QDateTime::currentDateTime();

}

        udp_sock.disconnectFromHost();
        udp_sock.close();

}
    else
    {

        QHostInfo info = QHostInfo::fromName("time.windows.com");
        QString ip_addr = info.addresses().first().toString();
        qDebug()<<((QString::fromLocal8Bit("不能连接到服务器%1，请检查网络！")).arg(ip_addr));
        cur_dt = QDateTime::currentDateTime();

}

    if(time_str)
    {

        QString str_dt = cur_dt.toString("yyyy-MM-dd hh:mm:ss");
        strncpy(time_str, str_dt.toStdString().c_str(), 200);

}
    qDebug()<<cur_dt.toString("yyyy-MM-dd hh:mm:ss");

    return cur_dt;

}
