#ifndef WIRELESSCONTROL_H
#define WIRELESSCONTROL_H

#include <QObject>

#include <QString>
#include <QStringList>
#include <QSysInfo>
#include <QMessageBox>

#include <QDebug>

#include <windows.h>
#include <wlanapi.h>

#include "globalDefine.h"

class wirelessControl : public QObject
{
    Q_OBJECT
public:
    explicit wirelessControl(QObject *parent = 0);

    QStringList getInterfaceList();
    QStringList getSSIDList();
    //WIF控制
    void wlanConnectInterface(QString ssid,QString psw);
    void updataSSIDList(int index);  //刷新SSID列表
    int findSSID(QString ssid); //查找是否有该ID；

    int getPswType(QString ssid);//获取加密类型 -2、无该ssid -1、不支持该加密类型 0、未加密 1、WEP 2、WAP/WAP2

    bool APIsConnected(); //该AP热点是否已经连接
    bool APHasProfile(); //该AP热点是否已经包含配置。
    void APDeleteProfile(); //删除热点配置


    QString currentSSID;


signals:
    void SSIDUpdata();
    void SSIDIndexChanged(int);

public slots:
    //槽
    void wireless_interface_changed(int i);
    void wireless_SSID_changed(int i);
    void set_ssid_psw(QString psw);
    QStringList get_ssid_list(void);

private:
    void initWireless();
    LPCWSTR str2LPCWSTR(QString str);

    //WIFI无线信号
    void searchNetworkDevice();
    void searchSSID(int index);

    PWLAN_INTERFACE_INFO_LIST    pIfList; //网卡列表
    PWLAN_INTERFACE_INFO         pIfInfo;
    PWLAN_AVAILABLE_NETWORK_LIST pBssList; //可用网络列表
    PWLAN_AVAILABLE_NETWORK      pBssEntry;
    void *hClient;

    unsigned long wlanMaxSupportVer;
    //WIFI控制
    bool wifiSetProfile(QString psw);
    bool wlanConnectSSID(QString psw);


    PWLAN_CONNECTION_PARAMETERS pConnPara;
    LPCWSTR wscProfileXML;
    DWORD dwReasonCode;  //失败原因码

    //模块wifi连接
    int getSSIDBssEntryIndex(QString ssid); //获取ssid的BSS

    bool refleshEntry();

    QStringList interfaceList;
    QStringList SSIDList;


    QString routerPsw;

    int currentWirelessIndex;
    int currentAPIndex;
};

#endif // WIRELESSCONTROL_H
