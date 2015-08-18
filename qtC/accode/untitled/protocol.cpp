#include "protocol.h"


#include <QDebug>


TransportProtocol_Typedef TransportProtocol;
//定义一个协议管理器
TransportProtocol_Manager_Typedef TransportProtocol_Manager;


//解包
static TransportProtocol_Result TransportProtocol_Unpacked(){

    int check_len=0;    //校验字节的长度
    u16 checksum=0;      //接收到的校验值
    u16 checksum_cal=0;  //计算得到的校验值
    u8 *checksum_pos=0; //校验值的偏移位置


    //帧格式错误，非法长度
    if(TransportProtocol_Manager.RecieveByteCount > MAX_FRAME_LENGTH || TransportProtocol_Manager.RecieveByteCount<MIN_FRAME_LENGTH){

        return FRAME_FORMAT_ERR;
  }
    //得到有效数据长度
    TransportProtocol_Manager.TransportProtocol->Data_Length = TransportProtocol_Manager.Buf[3];
    //校验字节的长度=接收的帧长度-4个字节的头-有效数据的长度
    check_len = TransportProtocol_Manager.RecieveByteCount - 4 - TransportProtocol_Manager.TransportProtocol->Data_Length;
    //校验值格式错误 校验字节个数不对
    if(check_len<1 || check_len>2){

        return CHECK_FORMAR_ERR;

  }
    //得到校验值的偏移地址
    checksum_pos = (u8 *)(4+TransportProtocol_Manager.TransportProtocol->Data_Length +TransportProtocol_Manager.Buf);
    if(check_len==1){
    checksum = (*checksum_pos)&0xff;
  }else if(check_len==2){
    checksum  = (*checksum_pos)&0xff;
        checksum_pos++;
        checksum <<=8;
        checksum |= *checksum_pos;
    }
    //计算 头和数据的校验值
    checksum_cal = TransportProtocol_Manager.Check(TransportProtocol_Manager.Buf,4+TransportProtocol_Manager.TransportProtocol->Data_Length);
    //校验错误
    if(checksum!=checksum_cal){
        return CHECK_ERR;
    }

    //设备地址
    TransportProtocol_Manager.TransportProtocol->Device_Address = TransportProtocol_Manager.Buf[0];
    //帧功能
    TransportProtocol_Manager.TransportProtocol->Function_Type = TransportProtocol_Manager.Buf[1];
    //帧序列 当前第几帧
    TransportProtocol_Manager.TransportProtocol->Sequence = TransportProtocol_Manager.Buf[2];
    //帧有效数据长度 (前面已获取)

    //帧数据
    TransportProtocol_Manager.TransportProtocol->Data = &TransportProtocol_Manager.Buf[4];

    //帧校验值
    TransportProtocol_Manager.TransportProtocol->Checksum = checksum_cal;


  return UPACKED_SUCCESS;
}


//打包
static void TransportProtocol_Packed(){
    u16 checksum=0;
    u8 *check_pos;  //校验值的偏移位置
  //设备地址
    TransportProtocol_Manager.Buf[0] = TransportProtocol_Manager.TransportProtocol->Device_Address;
    //帧功能
    TransportProtocol_Manager.Buf[1] = TransportProtocol_Manager.TransportProtocol->Function_Type;
    //帧序列
    TransportProtocol_Manager.Buf[2] = TransportProtocol_Manager.TransportProtocol->Sequence;
    //帧有效数据大小
    TransportProtocol_Manager.Buf[3] = TransportProtocol_Manager.TransportProtocol->Data_Length;
    //帧数据
    memcpy(&TransportProtocol_Manager.Buf[4],TransportProtocol_Manager.TransportProtocol->Data,TransportProtocol_Manager.TransportProtocol->Data_Length);
    //计算校验值
    checksum = TransportProtocol_Manager.Check(TransportProtocol_Manager.Buf,4+TransportProtocol_Manager.TransportProtocol->Data_Length);
    //校验值
    check_pos = TransportProtocol_Manager.Buf+4+TransportProtocol_Manager.TransportProtocol->Data_Length;

    if(checksum<256){
        (*check_pos) = checksum&0xff;
        //记录帧总长度
            TransportProtocol_Manager.FrameTotalLength = 4+TransportProtocol_Manager.TransportProtocol->Data_Length+1;
    }else{  //CRC16
        (*check_pos) = (u8)(checksum>>8)&0xff;  //高字节
        check_pos++;
        (*check_pos) = (u8)(checksum&0xff);			//低字节
        //记录帧总长度
        TransportProtocol_Manager.FrameTotalLength = 4+TransportProtocol_Manager.TransportProtocol->Data_Length+2;
    }


}


//初始化传输协议
//TransportProtocol：传输帧
//buf:收发缓冲区
//check:校验方式
//Checksum_Sum:和校验
//Checksum_XOR：异或校验
//Checksum_CRC8:CRC8校验
//Checksum_CRC16:CRC16校验

void  TransportProtocol_Init(TransportProtocol_Typedef *TransportProtocol,u8 *buf,u16 (*check)(u8 *,u16 len))
{

    //协议包
    TransportProtocol_Manager.TransportProtocol = TransportProtocol;
  //传输协议缓存
    TransportProtocol_Manager.Buf = buf;
    //选择校验方式
    TransportProtocol_Manager.Check = check;
    //打包函数
    TransportProtocol_Manager.Packed = TransportProtocol_Packed;
    //解包函数
    TransportProtocol_Manager.Unpacked = TransportProtocol_Unpacked;


}



//接收完整一帧数据，调用该函数解包
void protocolScan(u8 *buf,u16 *len)
{
    buf=buf;
    len=len;
    if(*len)//新周期内,没有收到任何数据,认为本次数据接收完成.
    {
        //获取接收的总字节数
        TransportProtocol_Manager.RecieveByteCount = *len;

        if(TransportProtocol_Manager.Unpacked()!=UPACKED_SUCCESS)
        {//解包失败

            qDebug("fail");

        }else{  //解包成功

                TransportProtocol_Manager.Packed();   //打包
                sendStr(TransportProtocol_Manager.Buf, TransportProtocol_Manager.FrameTotalLength);


                qDebug("success");

                checkCmd(&TransportProtocol);
                /*
                //设备地址
                OneByteToStr(TransportProtocol.Device_Address,RecieveBuf);
                //帧功能
                OneByteToStr(TransportProtocol.Function_Type,RecieveBuf);
                //帧序列
                OneByteToStr(TransportProtocol.Sequence,RecieveBuf);
                //有效数据长度
                OneByteToStr(TransportProtocol.Data_Length,RecieveBuf);
                //数据
                MultiByteToStr(TransportProtocol.Data,TransportProtocol.Data_Length,RecieveBuf);
                //校验值
                 if(TransportProtocol.Checksum<256){  //一个字节的校验值
                    OneByteToStr(TransportProtocol.Checksum,RecieveBuf);
                }else{  //两个字节的校验值
                    sprintf(RecieveBuf,"%d",TransportProtocol.Checksum);
                    LCD_ShowString(30,200,200,16,16,RecieveBuf);
                }
                */

        }

        *len=0;

    }
}

//执行对应命令
void checkCmd(TransportProtocol_Typedef *TransportProtocol)
{

    switch (TransportProtocol->Function_Type)
    {
        case 0x01:

            break;
        default:
            break;
    }
}

void sendStr(uchar *buf,uchar len)
{
    buf=buf;
    len=len;
}


u8 USART_RX_BUF[USART_REC_LEN];
u8 USART_TX_BUF[USART_REC_LEN];



// 空调条码专用




void BarCodeTranfer(u8 *ucBarDisp,u8 *ucBarCodeChk)
{




        ucBarDisp[0] = ucBarCodeChk[1] & 0x3f;
        ucBarDisp[1] = ucBarCodeChk[2] & 0x3f;
        ucBarDisp[2] = ucBarCodeChk[3] & 0x3f;
        ucBarDisp[3] = (ucBarCodeChk[1] >> 2) & 0x30;
        ucBarDisp[3] |= ((ucBarCodeChk[2] >> 4) & 0x0c);
        ucBarDisp[3] |= ((ucBarCodeChk[3] >> 6) & 0x03);

        ucBarDisp[4] = ucBarCodeChk[4] & 0x3f;
        ucBarDisp[5] = ucBarCodeChk[5] & 0x3f;
        ucBarDisp[6] = ucBarCodeChk[6] & 0x3f;
        ucBarDisp[7] = (ucBarCodeChk[4] >> 2) & 0x30;
        ucBarDisp[7] |= ((ucBarCodeChk[5] >> 4) & 0x0c);
        ucBarDisp[7] |= ((ucBarCodeChk[6] >> 6) & 0x03);

        ucBarDisp[8] = ucBarCodeChk[7] & 0x3f;
        ucBarDisp[9] = ucBarCodeChk[8] & 0x3f;
        ucBarDisp[10] = ucBarCodeChk[9] & 0x3f;
        ucBarDisp[11] = (ucBarCodeChk[7] >> 2) & 0x30;
        ucBarDisp[11] |= ((ucBarCodeChk[8] >> 4) & 0x0c);
        ucBarDisp[11] |= ((ucBarCodeChk[9] >> 6) & 0x03);

        ucBarDisp[12] = ucBarCodeChk[10] & 0x3f;
        ucBarDisp[13] = ucBarCodeChk[11] & 0x3f;
        ucBarDisp[14] = ucBarCodeChk[12] & 0x3f;
        ucBarDisp[15] = (ucBarCodeChk[10] >> 2) & 0x30;
        ucBarDisp[15] |= ((ucBarCodeChk[11] >> 4) & 0x0c);
        ucBarDisp[15] |= ((ucBarCodeChk[12] >> 6) & 0x03);

        ucBarDisp[16] = ucBarCodeChk[13] & 0x3f;
        ucBarDisp[17] = ucBarCodeChk[14] & 0x3f;
        ucBarDisp[18] = ucBarCodeChk[15] & 0x3f;
        ucBarDisp[19] = (ucBarCodeChk[13] >> 2) & 0x30;
        ucBarDisp[19] |= ((ucBarCodeChk[14] >> 4) & 0x0c);
        ucBarDisp[19] |= ((ucBarCodeChk[15] >> 6) & 0x03);

        ucBarDisp[20] =  ucBarCodeChk[16] & 0x3f;
        ucBarDisp[21] =  ucBarCodeChk[17] & 0x3f;

}

