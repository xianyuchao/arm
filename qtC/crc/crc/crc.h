#ifndef CRC_H
#define CRC_H

typedef unsigned char u8;
typedef unsigned char uchar;
typedef unsigned int uint;

#define LBFS    1   // 先发送低位，串口就是先发低位
//#define POLY    0x131    //x8+x5+x4+1    ，CRC-8/MAXIM
#define POLY    0x107    //x8+x2+x+1    ，CRC-8/ROHC
//#define CRCINIVAL   0x00    //有些是0xff,有些是0x00
#define CRCINIVAL   0xff    //有些是0xff,有些是0x00



uchar calcrc_bytes(uchar *p,uchar len);

uchar calcrc_1byte(uchar abyte);

uchar xchange(uchar x);

uchar calx1byte(uchar data);
uchar calx1bytes(uchar *p,uchar len);

#endif // CRC_H

