#ifndef TESTLIB_H
#define TESTLIB_H

#include "untitled_global.h"
#include <qbytearray.h>
#include <qstring.h>
#include <qdebug.h>

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long u64;


class UNTITLEDSHARED_EXPORT testlib
{

public:
    testlib();
    void qbytearray2uchar(QByteArray *from,unsigned char * to,int len);// qbytearray 转换为 uchar
    void uchar2qbytearray(unsigned char  *from,QByteArray* to,int len);// uchar 转换为  qbytearray
    void printuchar(unsigned char  *b,int len);// 用qdebug 打印uchar ,用16进制
    void uchar2qstring(unsigned char  *from,QString* to,int len);// 将uchar 合为一串qstring  "0x11 0x55..."
    void uchar2qstringAscii(unsigned char  *from,QString* to,int len);// 例如 0x32 0x33 合成qstring "23"
    void qstring2uchar(QString *str,unsigned char *to ,int len);// "AAA "  转为 [65,65,65]
    u16 Checksum_Sum(u8* buf,u16 len);   //和校验 所有字节之和为0
    u16 Checksum_XOR(u8* buf, u16 len);	//异或校验，所有字节异或
    u16 Checksum_CRC8(u8 *buf,u16 len);	//CRC8 校验
    u16 Checksum_CRC16(u8 *buf,u16 len);//CRC16 校验

};

#endif // TESTLIB_H
