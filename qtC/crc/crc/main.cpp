#include <QCoreApplication>


#include <qdebug.h>


#include "crc.h"

int main(int argc, char *argv[])
{
    uchar x[]={0x01,0x02,0x03,0xff};
    uchar res;
    QCoreApplication a(argc, argv);

    res=calx1bytes(x,sizeof(x));




    printf("%x",(res));
    return a.exec();
}
