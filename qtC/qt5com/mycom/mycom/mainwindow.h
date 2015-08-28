#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QtSerialPort/QSerialPort>
//#include <QObject>
#include <qdebug.h>


#include "testlib.h"

namespace Ui {
class MainWindow;
}

const unsigned char cmd_start[]={0x11 ,0x03 ,0x0C ,0x02 ,0x1E ,0xC0};// 启动
const unsigned char cmd_stop[]={0x11 ,0x03 ,0x0C ,0x01 ,0x1E ,0xC1};// 停止
const unsigned char cmd_readpm[]={0x11 ,0x02 ,0x0B ,0x01,0xE1};// 读结果
const unsigned char cmd_persistpm[]={0x11 ,0x03 ,0x0D ,0xff,0xfb,0xE5};// 设置连续采样

#define PM25_REC_START 0x16     // 头码

//PM25通信协议相关
#define U8_START_STOP_CMD		0x0C	//开启、关闭粉尘测量
#define U8_GET_RESULT_CMD		0x0B	//读取粉尘测量结果
#define U8_WRITE_USEROPT_CMD	0x1C	//写入用户粉尘校正系数
#define U8_SET_READ_TIME_CMD	0x0D	//设置与读取粉尘测量时间
#define U8_SET_READ_MODE_CMD	0x05	//设置与读取定时测量工作模式
#define U8_SET_READ_DYNAMIC_CMD 0x06	//设置与读取动态测量工作模式


#define U8_START_ACUQUIRE		0x02	//开启测量
#define U8_STOP_ACUQUIRE		0x01	//停止测量

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QSerialPort serialPort;
    QTimer      m_timer;
    QByteArray  m_readData;


    int pm05Res;// 0.5 um
    int pm25Res;// 2.5 um
    int pm10Res;// 10 um

    uchar GetPM25CRC(uchar ucInputDat[],uchar ucDatLength);
    int getPm25Res(uchar *buf,int len);

    testlib tl;

private slots:
    void handleReadyRead();
    void handleTimeout();
    void handleError(QSerialPort::SerialPortError error);

    void on_pushButton_clicked();
};

#endif // MAINWINDOW_H
