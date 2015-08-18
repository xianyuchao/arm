#include "crc.h"



uchar calcrc_1byte(uchar abyte)
{
    uchar i,crc_1byte;
    crc_1byte=0;                //设定crc_1byte初值为0
    for(i = 0; i < 8; i++)
    {
        if(((crc_1byte^abyte)&0x01))
        {
            crc_1byte^=0x18;
            crc_1byte>>=1;
            crc_1byte|=0x80;
        }
        else
            crc_1byte>>=1;
        abyte>>=1;
    }

    return crc_1byte;

}

uchar calcrc_bytes(uchar *p,uchar len)
{
    uchar crc=0;
    while(len--) //len为总共要校验的字节数
    {
        crc=calcrc_1byte(crc^*p++);
    }
    return crc;  //若最终返回的crc为0，则数据传输正确
}

uchar xchange(uchar x)
{
    uchar temp=0x01,res=0,temp2=0x80;

    for(int i=0;i<8;i++)
    {
        if(x&temp)
        {
            res|=(temp2);
        }
        temp<<=1;
        temp2>>=1;
    }
    return res;
}
uchar calx1byte(uchar data)
{
    uint res;
    data=xchange(data);
    res=data;
    for(int i=0;i<8;i++)
    {
        res<<=1;
        if(res&0x100)
        {
            res=res^POLY;
        }
    }

    data=res;
    data=xchange(data);
    return (uchar)data;
}

uchar calx1bytes(uchar *p,uchar len)
{
    uchar crc=CRCINIVAL;
    while(len--) //len为总共要校验的字节数
    {
        crc=calx1byte(crc^*p++);
    }
    return crc;  //若最终返回的crc为0，则数据传输正确
}
