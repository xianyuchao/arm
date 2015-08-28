#include <QDebug>
#include    <QString>
#include    <qbytearray.h>

#include "jianrong.h"

void qbytearray2uchar(QByteArray *from,unsigned char * to,int len)
{
    int i=0;
    while(len--)
    {
        *to++=from->at(i++);
    }
}

void uchar2qbytearray(unsigned char  *from,QByteArray* to,int len)
{
    while(len--)
    {
        to->append(*from++);
    }
}

void printuchar(unsigned char  *b,int len)
{
    QString str;
    while(len--)
    {
        str.append(QString::number(*b,16));//
        str.append(" ");
        b++;
    }
    qDebug()<<str;
}

//void uchar2qint(unsigned char from,qint8 to)
//{}
