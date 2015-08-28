#ifndef GOLBALDEFINE_H
#define GOLBALDEFINE_H
#include <QtCore>

#include <qdatetime.h>

#define D2LISTSIZE 5
#define D2STRSIZE 45
#define SNSTRSIZT 22   //SN长度
#define CODE2SIZT 64 //二维码数据长度
#define NETHEADSIZE 40

#define MODULE_DEFAULT_PSW "12345678"
#define HEARTBEAT_TIME 1500

#define WAIT_SSIDAPPEAR_TIME 500 //等待SSID出现时间
#define SSIDAPPEAR_TIMES 14 //AP等待次数

#define WAIT_APCONNECT_TIME 300//3000 //等待连接AP的时间
#define WAIT_APCONNECT_TIMES 7//20 //等待AP连接成功次数
#define APCONNECT_TIMES 4//20 //连接AP次数

#define TCP_CONNECT_TIMES 5
#define TCP_DELAY_TIME 500

#define WAIT_RECORD_ANSWER_TIME 10000 //等待烧写应答时间

#define AP_DEFAULT_IP "192.168.1.1" //AP连接默认模块的IP地址
#define TCP_DEFAULT_PORT "6444"

#define UDP_DEFAULT_PORT 7083     // 默认监听UDP端口

#define CHECK_INTERFACE_CONNECT_TIME 1000 //检测网络连接状态

#define SNDIR "c:\\SN.txt"    //SN文件路径



extern QMap <QString,int> qMapSn;

#define SNTIMEOUT       5//超时 时间，单位秒

#define ALARM_COLOR     QColor(255,0,0)

#endif // GOLBALDEFINE_H
