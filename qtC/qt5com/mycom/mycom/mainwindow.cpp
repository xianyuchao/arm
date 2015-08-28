#include "mainwindow.h"
#include "ui_mainwindow.h"


#include "jianrong.h"

#include <qlibrary.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //QLibrary *testlib=new QLibrary("F:/qtC/mylib/build-untitled-Desktop_Qt_5_4_0_MinGW_32bit-Debug/debug/libuntitled.a");
    //testlib->load();


    serialPort.setPortName("COM6");

    serialPort.setBaudRate(QSerialPort::Baud9600);

    serialPort.open(QIODevice::ReadWrite);


    connect(&serialPort, SIGNAL(readyRead()), SLOT(handleReadyRead()));
    connect(&serialPort, SIGNAL(error(QSerialPort::SerialPortError)), SLOT(handleError(QSerialPort::SerialPortError)));
    connect(&m_timer, SIGNAL(timeout()), SLOT(handleTimeout()));

    m_timer.start(200);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleReadyRead()
{
    m_readData.append(serialPort.readAll());

    if (!m_timer.isActive())
        m_timer.start(200);
}

void MainWindow::handleTimeout()
{
    static int step=0;

    if (m_readData.isEmpty()) {
        //m_standardOutput << QObject::tr("No data was currently available for reading from port %1").arg(m_serialPort->portName()) << endl;
    } else {
        //m_standardOutput << QObject::tr("Data successfully received from port %1").arg(m_serialPort->portName()) << endl;
        //m_standardOutput << m_readData << endl;

         char *x=m_readData.data();
        //qDebug()<<x;
        if(getPm25Res((uchar*)x,m_readData.size()) == 1)
        {
            QString out;
            out+="0.5um:";
            out+=QString::number(pm05Res);
            out+="\n";

            out+="2.5um:";
            out+=QString::number(pm25Res);
            out+="\n";

            out+="10um:";
            out+=QString::number(pm10Res);
            out+="\n";

             ui->label_2->setText(out);
        }
        m_readData.clear();


    }

    QByteArray xx;

    switch (step) {
    case 0:
        tl.uchar2qbytearray((unsigned char*)cmd_stop,&xx,sizeof(cmd_stop));
        serialPort.write(xx);//
        step++;
        break;
    case 1:
        tl.uchar2qbytearray((unsigned char*)cmd_start,&xx,sizeof(cmd_start));
        serialPort.write(xx);//
        step++;
        break;
    case 2:
        tl.uchar2qbytearray((unsigned char*)cmd_persistpm,&xx,sizeof(cmd_persistpm));
        serialPort.write(xx);//
        step++;
        break;
    default:

        tl.uchar2qbytearray((unsigned char*)cmd_readpm,&xx,sizeof(cmd_readpm));
        serialPort.write(xx);// 0.5 秒查一次结果
        break;
    }


    //qDebug()<<xx;

    //QCoreApplication::quit();
}

void MainWindow::handleError(QSerialPort::SerialPortError serialPortError)
{
    if (serialPortError == QSerialPort::ReadError) {
        //m_standardOutput << QObject::tr("An I/O error occurred while reading the data from port %1, error: %2").arg(m_serialPort->portName()).arg(m_serialPort->errorString()) << endl;
        //QCoreApplication::exit(1);
        qDebug()<<"ERROR";
    }
}

void MainWindow::on_pushButton_clicked()
{


    //QString  xx= ui->textEdit_2->data;
    //QByteArray ff("fff");
    //QByteArray ff=ui->textEdit_2->data;
    //serialPort.write(ff);
    QString a=ui->textEdit_2->toPlainText();
    QByteArray xx=a.toLatin1();

    tl.uchar2qbytearray((unsigned char*)cmd_start,&xx,sizeof(cmd_start));
    serialPort.write(xx);
   qDebug()<< a;
}

uchar MainWindow::GetPM25CRC(uchar ucInputDat[],uchar ucDatLength)//计算灰尘传感器的校验码
{
    uchar ucCheckSum, i;

    ucCheckSum = 0;

    for(i = 0; i < ucDatLength; i++)
    {
        ucCheckSum += ucInputDat[i];
    }
    ucCheckSum =256 - ucCheckSum;

    return (ucCheckSum);
}

int MainWindow::getPm25Res(uchar *buf,int len)// 灰尘传感器命令返回，数据解释
{
    testlib tl;

    if ((buf[len-1] == GetPM25CRC(&buf[0],len-1))&&
            (buf[0] == PM25_REC_START))
    {
        switch(buf[2])
        {
            case U8_START_STOP_CMD:
                if(buf[3]==0x01)
                    ui->label->setText("工作中");
                else
                    ui->label->setText("停止");
                break;
            case U8_SET_READ_TIME_CMD:
                //PM25ContinueAcqCmdRecDeal(buf);
                break;
            case U8_GET_RESULT_CMD:
                //PM25ReadResultCmdRecDeal(buf);
                pm05Res = buf[3]*(256^3)+buf[4]*(256^2)+buf[5]*256 + buf[6];
                pm25Res = buf[7]*(256^3)+buf[8]*(256^2)+buf[9]*256 + buf[10];
                pm10Res = buf[11]*(256^3)+buf[12]*(256^2)+buf[13]*256 + buf[14];


                tl.printuchar(buf,len);

                break;
            default:
                break;

        }
//qDebug()<<"decode correct";
        return 1;
    }
    //qDebug()<<"decode error";
    return 0;
}
