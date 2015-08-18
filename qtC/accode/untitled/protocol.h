#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "testlib.h"

#define USART_REC_LEN  		128
extern u8 USART_RX_BUF[USART_REC_LEN];
extern u8 USART_TX_BUF[USART_REC_LEN];

//传输帧对象
typedef struct{
    //最大帧长度
    #define MAX_FRAME_LENGTH 261
    //最小帧长度
    #define MIN_FRAME_LENGTH  5
    //设备地址
    u8 Device_Address;
    //帧功能
    u8 Function_Type;
    //帧序列
    u8 Sequence;
    //有效数据长度
    u8 Data_Length;
    //数据
    u8 *Data;
    //校验值
    u16 Checksum;

}TransportProtocol_Typedef;



//传输结果
typedef enum{
 //帧格式错误
    FRAME_FORMAT_ERR = 1,
    //校验值格式错误
    CHECK_FORMAR_ERR = 2,
    //校验值错位
    CHECK_ERR = 3,
    //解包成功
    UPACKED_SUCCESS = 4


}TransportProtocol_Result;


//协议管理器
 typedef  struct{

    //传输帧
 TransportProtocol_Typedef * TransportProtocol;
    //接收的字节数
    u32  RecieveByteCount;

    //传输帧缓存
    u8* Buf;
    //帧总长度
    u16 FrameTotalLength;
    //解包函数
    TransportProtocol_Result (*Unpacked)(void);
    //打包函数
    void (*Packed)(void);
    //校验函数
    u16 (*Check)(u8 *,u16 len);

}TransportProtocol_Manager_Typedef;


//外部声明协议管理器
extern TransportProtocol_Manager_Typedef TransportProtocol_Manager;
extern TransportProtocol_Typedef TransportProtocol;
//初始化传输协议
void  TransportProtocol_Init(TransportProtocol_Typedef *TransportProtocol,u8 *buf,u16 (*check)(u8 *,u16 len));

void protocolScan(u8 *buf,u16 *len);
void checkCmd(TransportProtocol_Typedef *TransportProtocol);
void sendStr(uchar *buf,uchar len);

void BarCodeTranfer(u8 *ucBarDisp,u8 *ucBarCodeChk);

#endif // PROTOCOL_H
