#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include    <QString>

#include "protocol.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    u8 code[22],*p;
    p=code;

    *p++=0xBB;
    *p++=0x31;
    *p++=0xF0;
    *p++=0x54;
    *p++=0x58;
    *p++=0xD1;
    *p++=0x46;
    *p++=0x91;
    *p++=0x11;
    *p++=0x61;
    *p++=0xFD;
    *p++=0x3D;
    *p++=0x26;
    *p++=0x40;
    *p++=0x51;
    *p++=0x18;
    *p++=0x00;
    *p++=0x01;
    *p++=0x0F;
    *p++=0x33;
    QString x;
    tl.uchar2qstring(code,&x,20);
    qDebug()<<x;
    //tl.printuchar(code,20);

    u8 test[30];
    QByteArray em;
    em.clear();



    test[0]=0x31;
    test[1]=0x32;
    test[2]=0x32;

    QString ff("555");

    tl.qstring2uchar(&ff,test,3);
    tl.printuchar(test,3);

    tl.uchar2qstringAscii(test,&ff,3);
    //qDebug()<<ff;


    BarCodeTranfer(test,code);

    //tl.printuchar(test,22);
    //    uchar2qbytearray(test,&em,5);
    //    qDebug()<<em;

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_textEdit_textChanged()
{
    QString a=ui->textEdit->toPlainText();
    u16 len=a.length();

    ui->label_2->setText("条码长度"+QString::number(len));

    if(len==22)
    {
        QByteArray content=a.toLatin1();
        u8 xx[50];
        tl.qbytearray2uchar(&content,xx,content.size());
        u8 crc8=tl.Checksum_CRC8(xx,len);
        ui->label_3->setText("CRC8:"+QString::number(crc8)+"(0x"+QString::number(crc8,16)+")");

        u16 checksum=tl.Checksum_Sum(xx,len);
        ui->label_4->setText("校验和："+QString::number(checksum)+"(0x"+QString::number(checksum,16)+")");

        u16 res=checksum^crc8;
        ui->label_5->setText("异或最终结果："+QString::number(res)+"(0x"+QString::number(res,16)+")");
    }
    else
    {

        ui->label_3->setText("CRC8:");
        ui->label_4->setText("校验和：");
        ui->label_5->setText("异或最终结果：");

    }


}
