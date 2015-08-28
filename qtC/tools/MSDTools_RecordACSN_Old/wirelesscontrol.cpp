#include "wirelesscontrol.h"

wirelessControl::wirelessControl(QObject *parent) :
    QObject(parent)
{
    initWireless(); //初始化无线
}

QStringList wirelessControl::getInterfaceList()
{
    return interfaceList;
}

QStringList wirelessControl::getSSIDList()
{
qDebug()<<"currentIndex:"<<currentAPIndex<<"pBssList:"<<QString((char *)pBssEntry->dot11Ssid.ucSSID);
    return SSIDList;
}

//初始化无线
void wirelessControl::initWireless()
{
    //获取操作系统版本
    switch (QSysInfo::WindowsVersion)
    {
    case QSysInfo::WV_XP:
    case QSysInfo::WV_2003:
        wlanMaxSupportVer = 1;
        break;
    case QSysInfo::WV_VISTA:
    case QSysInfo::WV_WINDOWS7:
    case QSysInfo::WV_WINDOWS8:
    case QSysInfo::WV_WINDOWS8_1:
        wlanMaxSupportVer = 2;
        break;
    default:
        //QMessageBox::information(this,tr("提示"),tr("不支持该系统，谢谢！"));
        wlanMaxSupportVer = 0;
        exit(0);
        break;
    }
    //获取ssid
    pIfList = NULL; //网卡列表
    pIfInfo = NULL;
    pBssList = NULL; //可用网络列表
    pBssEntry = NULL;
    hClient = NULL;

    dwReasonCode = 0;

    searchNetworkDevice();
    searchSSID(0);

    wscProfileXML = NULL;
}

LPCWSTR wirelessControl::str2LPCWSTR(QString str)
{
    int nXMLLenght = 0;
    nXMLLenght = MultiByteToWideChar(CP_ACP, 0, str.toLatin1().data(), -1, NULL, 0);
    wchar_t *wsc = (wchar_t *) new wchar_t[nXMLLenght];
    MultiByteToWideChar(CP_ACP, 0, str.toLatin1().data(), -1, wsc, nXMLLenght);
    //delete []wscProfileXML;
    return wsc;
}
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<WIFI无线网卡获取与控制>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//搜索无线网卡设备
void wirelessControl::searchNetworkDevice()
{
    unsigned long dwResult,dwCurVersion;
    QString interfaceName;
    //打开WLAN服务
    dwResult = WlanOpenHandle(wlanMaxSupportVer, NULL, &dwCurVersion,&hClient);
    if (dwResult != ERROR_SUCCESS)
    {
        //QMessageBox::information(this,tr("提示"),tr("无法打开WLAN句柄，错误代码：%1").arg(dwResult));
        //wprintf(L"WlanOpenHandle failed with error: %u\n", dwResult);
        return ;
    }

    //枚举WLAN接口
    dwResult = WlanEnumInterfaces(hClient, NULL, &pIfList);
    if (dwResult != ERROR_SUCCESS)
    {
        //QMessageBox::information(this,tr("提示"),tr("无法打开WLAN接口，错误代码：%1").arg(dwResult));
        // wprintf(L"WlanEnumInterfaces failed with error: %u\n", dwResult);
        return ;
        // You can use FormatMessage here to find out why the function failed
    }
    else
    {
        for (int i = 0; i < (int) pIfList->dwNumberOfItems; i++)
        {
            pIfInfo = (WLAN_INTERFACE_INFO *) &pIfList->InterfaceInfo[i];

            interfaceName = QString::fromWCharArray(pIfInfo->strInterfaceDescription);
            interfaceList.append(interfaceName);
            //ui->wirelessComboBox->addItem(interfaceName);
            qDebug()<<"Interface:"<<interfaceName<<endl;

        }
    }
    wireless_interface_changed(0);
}

//搜索SSID
void wirelessControl::searchSSID(int index)
{
    unsigned long dwResult;
    char *pNetwork;
    QString SSIDName;

    //SSID列表
    if(pIfList->dwNumberOfItems == 0)
    {
        //QMessageBox::information(this,tr("提示"),tr("未找到无线网卡设备！"));
        qDebug()<<"Can not find Interface!"<<endl;
        return;
    }
    if(SSIDList.size() != 0)
    {
        SSIDList.clear();
        //WlanFreeMemory(pBssList);
        //pBssList = NULL;
    }

    pIfInfo = (WLAN_INTERFACE_INFO *) &pIfList->InterfaceInfo[index];
    WlanScan(hClient,&pIfInfo->InterfaceGuid,NULL,NULL,NULL);
    //qDebug()<<"guid:"<<QString::fromWCharArray(pIfInfo->strInterfaceDescription)<<endl;
    dwResult = WlanGetAvailableNetworkList(hClient, &pIfInfo->InterfaceGuid,0, NULL, &pBssList);
    if (dwResult != ERROR_SUCCESS)
    {
        //QMessageBox::information(this,tr("提示"),tr("无法获取可用无线网络，错误代码：%1").arg(dwResult));
        //wprintf(L"WlanGetAvailableNetworkList failed with error: %u\n",dwResult);
        qDebug()<<"Can not get the available network!"<<endl;
        dwResult = 1;
        // You can use FormatMessage to find out why the function failed
    }
    else
    {
        // wprintf(L"  Num Entries: %lu\n\n", pBssList->dwNumberOfItems);
        for (DWORD i = 0; i < pBssList->dwNumberOfItems; i++)
        {
            pBssEntry = (WLAN_AVAILABLE_NETWORK *) & pBssList->Network[i];

            if (pBssEntry->dot11Ssid.uSSIDLength != 0)
            {
                pNetwork = (char*) pBssEntry->dot11Ssid.ucSSID;

                SSIDName = QString::fromUtf8(pNetwork);
                //ui->routerSSIDComboBox->addItem(SSIDName);
                SSIDList.append(SSIDName);
                //qDebug()<<"ssid:"<<SSIDName;
            }
        }
    }
    //emit SSIDIndexChanged(hasConnectedInterfaceIndex);
    //wireless_SSID_changed(hasConnectedInterfaceIndex);
    wireless_SSID_changed(0);
}

//设置Profile
bool wirelessControl::wifiSetProfile(QString psw)
{
    QString szProfileXML;  //Profile XML流
    unsigned long dwResult;

    /*组合参数XML码流*/
    QString szTemp;
    if(APHasProfile())
    {
        WlanDeleteProfile(hClient,&pIfInfo->InterfaceGuid,pBssEntry->strProfileName,NULL);
    }
    /*头*/
    szProfileXML += QString("<?xml version=\"1.0\"?><WLANProfile xmlns=\"http://www.microsoft.com/networking/WLAN/profile/v1\"><name>");
    /*name，一般与SSID相同*/
    szTemp = QString((char*)pBssEntry->dot11Ssid.ucSSID);
    szProfileXML += szTemp;
    /*SSIDConfig*/
    szProfileXML += QString("</name><SSIDConfig><SSID><name>");
    szProfileXML += szTemp;
    szProfileXML += QString("</name></SSID></SSIDConfig>");
    /*connectionType*/
    szProfileXML += QString("<connectionType>");

    switch(pBssEntry->dot11BssType)
    {
    case dot11_BSS_type_infrastructure:
        szProfileXML += "ESS";
        break;
    case dot11_BSS_type_independent:
        szProfileXML += "IBSS";
        break;
    case dot11_BSS_type_any:
        szProfileXML += "Any";
        break;
    default:
        //wprintf(L"Unknown BSS type");
        return false;
    }

    szProfileXML += QString("</connectionType><MSM><security><authEncryption><authentication>");
    switch( pBssEntry->dot11DefaultAuthAlgorithm)
    {
        case DOT11_AUTH_ALGO_80211_OPEN:
            szProfileXML += "open";
            //wprintf(L"Open 802.11 authentication\n");
            break;
        case DOT11_AUTH_ALGO_80211_SHARED_KEY:
            szProfileXML += "shared";
            //wprintf(L"Shared 802.11 authentication");
            break;
        case DOT11_AUTH_ALGO_WPA:
            szProfileXML += "WPA";
            //wprintf(L"WPA-Enterprise 802.11 authentication\n");
            break;
        case DOT11_AUTH_ALGO_WPA_PSK:
            szProfileXML += "WPAPSK";
            //wprintf(L"WPA-Personal 802.11 authentication\n");
            break;
        case DOT11_AUTH_ALGO_WPA_NONE:
            szProfileXML += "none";
            //wprintf(L"WPA-NONE,not exist in MSDN\n");
            break;
        case DOT11_AUTH_ALGO_RSNA:
            szProfileXML += "WPA2";
            //wprintf(L"WPA2-Enterprise 802.11 authentication\n");
            break;
        case DOT11_AUTH_ALGO_RSNA_PSK:
            szProfileXML += "WPA2PSK";
            //wprintf(L"WPA2-Personal 802.11 authentication\n");
            break;
        default:
           //wprintf(L"Unknown authentication");
           return false;
    }
    szProfileXML += QString("</authentication><encryption>");

    switch(pBssEntry->dot11DefaultCipherAlgorithm)
    {
        case DOT11_CIPHER_ALGO_NONE:
            szProfileXML += "none";
            break;
        case DOT11_CIPHER_ALGO_WEP40:
            szProfileXML += "WEP";
            break;
        case DOT11_CIPHER_ALGO_TKIP:
            szProfileXML += "TKIP";
            break;
        case DOT11_CIPHER_ALGO_CCMP:
            szProfileXML += "AES";
            break;
        case DOT11_CIPHER_ALGO_WEP104:
            szProfileXML += "WEP";
            break;
        case DOT11_CIPHER_ALGO_WEP:
            szProfileXML += "WEP";
            break;
        case DOT11_CIPHER_ALGO_WPA_USE_GROUP:
            //wprintf(L"USE-GROUP not exist in MSDN");
        default:
            //wprintf(L"Unknown encryption");
            return false;
    }

    szProfileXML += QString("</encryption></authEncryption><sharedKey><keyType>passPhrase</keyType><protected>false</protected><keyMaterial>");
    szProfileXML += psw;
    /*尾*/
    szProfileXML += QString("</keyMaterial></sharedKey></security></MSM></WLANProfile>");
    /*XML码流转换成双字节*/
    wscProfileXML = str2LPCWSTR(szProfileXML);
    //qDebug()<<QString::fromWCharArray(wscProfileXML)<<endl;
    if(NULL == wscProfileXML)
    {
        //wprintf(L"Change wscProfileXML fail\n");
        return false;
    }
     /*设置网络参数*/
    dwResult = WlanSetProfile(hClient, &pIfInfo->InterfaceGuid,
        0x00, wscProfileXML, NULL, FALSE, NULL, &dwReasonCode);
    if(ERROR_SUCCESS != dwResult)
    {
        switch (dwResult)
        {
        case ERROR_INVALID_PARAMETER:
            //wprintf(L"Para is NULL\n");
            break;
        case ERROR_INVALID_HANDLE:
            //wprintf(L"Failed to INVALID HANDLE \n");
            break;
        case ERROR_NOT_ENOUGH_MEMORY:
            //wprintf(L"Failed to allocate memory \n");
            break;
        case ERROR_BAD_PROFILE:
            //wprintf(L"The profile specified by strProfileXml is not valid \n");
            break;
        case ERROR_ALREADY_EXISTS:
            //wprintf(L"strProfileXml specifies a network that already exists \n");
            break;
        case ERROR_ACCESS_DENIED:
            //wprintf(L"The caller does not set the profile. \n");
            break;
        default:
            dwResult = GetLastError();
            //wprintf(L"WlanSetProfile Fail： %wd\n", dwResult);
            break;
        }
        if (dwResult != 183)
        {
            return false;
        }
    }
    return true;
}

//连接SSID
bool wirelessControl::wlanConnectSSID(QString psw)
{
    unsigned long dwResult;
    wifiSetProfile(psw);
    pConnPara = (PWLAN_CONNECTION_PARAMETERS)calloc(1, sizeof(WLAN_CONNECTION_PARAMETERS));
    //设置网络连接参数
    if(NULL == pConnPara)
    {
        wprintf(L"pConnPara fail\n");
    }
    pConnPara->wlanConnectionMode = (WLAN_CONNECTION_MODE)0;	//XP SP2,SP3 must be 0
    pConnPara->strProfile = str2LPCWSTR(QString::fromUtf8((char *)pBssEntry->dot11Ssid.ucSSID));//pProfileXml;
    pConnPara->pDot11Ssid = &pBssEntry->dot11Ssid;
    pConnPara->pDesiredBssidList = NULL;	//XP SP2,SP3 must be NULL
    pConnPara->dot11BssType = pBssEntry->dot11BssType;
    pConnPara->dwFlags = 0x00000000;	//XP SP2,SP3 must be 0

    //qDebug()<<"ConnectGuid:"<<QString::fromWCharArray(pIfInfo->strInterfaceDescription)<<endl;
    dwResult = WlanConnect(hClient, &pIfInfo->InterfaceGuid, pConnPara, NULL);
    if(ERROR_SUCCESS != dwResult)
    {
        switch (dwResult)
        {
        case ERROR_INVALID_PARAMETER:
            qDebug("Para is NULL\n");
            break;
        case ERROR_INVALID_HANDLE:
            wprintf(L"Failed to INVALID HANDLE \n");
            break;
        case ERROR_NOT_ENOUGH_MEMORY:
            wprintf(L"Failed to allocate memory \n");
            break;
        case ERROR_ACCESS_DENIED:
            wprintf(L"The caller does not have sufficient permissions. \n");
            break;
        default:
            dwResult = GetLastError();
            wprintf(L"WlanConnect Fail： %wd\n", dwResult);
            break;
        }
        free(pConnPara);
        return false;
    }
    free(pConnPara);
    return true;
}

void wirelessControl::updataSSIDList(int index)
{
    int ssidIndex;
    QString ssid = currentSSID;
    //qDebug()<<"name:"<<currentSSID<<endl;
    WlanFreeMemory(pBssEntry);
    WlanFreeMemory(pBssList);
    searchSSID(index);
    ssidIndex = getSSIDBssEntryIndex(ssid);
    //qDebug()<<"ssid:"<<ssidIndex<<endl;
    if(ssidIndex < 0)
    {
        ssidIndex = 0;
    }
    emit SSIDUpdata();
    emit SSIDIndexChanged(ssidIndex);
}

int wirelessControl::findSSID(QString ssid)
{
    int index;
    refleshEntry();
    index = SSIDList.indexOf(ssid);
    //qDebug()<<"findSSID:"<<ssid<<":"<<index<<endl;
    return index;
}

//获取加密类型 -2、无该ssid -1、不支持该加密类型 0、未加密 1、WEP 2、WAP/WAP2
int wirelessControl::getPswType(QString ssid)
{
    int index = getSSIDBssEntryIndex(ssid);
    int auth;
    int cipher;
    if(index == -1)
    {
        return -1;
    }
    PWLAN_AVAILABLE_NETWORK pNetworkSSID = (WLAN_AVAILABLE_NETWORK *) & pBssList->Network[index];
    auth = pNetworkSSID->dot11DefaultAuthAlgorithm;
    cipher = pNetworkSSID ->dot11DefaultCipherAlgorithm;
    switch (auth)
    {
    case DOT11_AUTH_ALGO_80211_OPEN :
        switch (cipher)
        {
        case DOT11_CIPHER_ALGO_NONE:
            return 0;
            break;
        case DOT11_CIPHER_ALGO_WEP40 :
        case DOT11_CIPHER_ALGO_WEP104:
        case DOT11_CIPHER_ALGO_WEP:
            return 1;
        default:
            return -1;
            break;
        }
        break;
    case DOT11_AUTH_ALGO_WPA:
    case DOT11_AUTH_ALGO_WPA_PSK:
    case DOT11_AUTH_ALGO_WPA_NONE:
    case DOT11_AUTH_ALGO_RSNA:
    case DOT11_AUTH_ALGO_RSNA_PSK:
        return 2;
        break;
    default:
        return -1;
        break;
    }
}

void wirelessControl::wlanConnectInterface(QString ssid,QString psw)
{
    int index;
    index = getSSIDBssEntryIndex(ssid);
    if(index == -1)
    {
        qDebug()<<"Can not find the module";
        return;
    }
    //qDebug()<<"indexchange:"<<index<<endl;
    wireless_SSID_changed(index);
    wlanConnectSSID(psw);
}

void wirelessControl::set_ssid_psw(QString psw)
{
    //qDebug()<<"psw"<<psw;
    routerPsw = psw;
}

int wirelessControl::getSSIDBssEntryIndex(QString ssid)
{
    return SSIDList.indexOf(ssid); //ui->routerSSIDComboBox->findText(ssid);
}

bool wirelessControl::refleshEntry()
{
    unsigned long dwResult;
    char *pNetwork;
    QString SSIDName;
    int index;
    QString ssid = QString::fromUtf8((char *)pBssEntry->dot11Ssid.ucSSID);
    //WlanScan(hClient,&pIfInfo->InterfaceGuid,NULL,NULL,NULL);
    dwResult = WlanGetAvailableNetworkList(hClient, &pIfInfo->InterfaceGuid,0, NULL, &pBssList);
    if (dwResult != ERROR_SUCCESS)
    {
        //QMessageBox::information(this,tr("提示"),tr("无法获取可用无线网络，错误代码：%1").arg(dwResult));
        //wprintf(L"WlanGetAvailableNetworkList failed with error: %u\n",dwResult);
        qDebug()<<"Can not get the available network!"<<endl;
        dwResult = 1;
        // You can use FormatMessage to find out why the function failed
        return false;
    }
    else
    {
        SSIDList.clear();
        // wprintf(L"  Num Entries: %lu\n\n", pBssList->dwNumberOfItems);
        for (DWORD i = 0; i < pBssList->dwNumberOfItems; i++)
        {
            pBssEntry = (WLAN_AVAILABLE_NETWORK *) & pBssList->Network[i];

            if (pBssEntry->dot11Ssid.uSSIDLength != 0)
            {
                pNetwork = (char*) pBssEntry->dot11Ssid.ucSSID;

                SSIDName = QString::fromUtf8(pNetwork);
                //ui->routerSSIDComboBox->addItem(SSIDName);
                SSIDList.append(SSIDName);
                //qDebug()<<"ssid:"<<SSIDName<<endl;
            }
        }
    }
    index = getSSIDBssEntryIndex(ssid);
    if(index == -1)
    {
        qDebug()<<"Can not find the module";
        return false;
    }
    wireless_SSID_changed(index);
    return true;
}

bool wirelessControl::APIsConnected()
{
    if(!refleshEntry())
    {
        return false;
    }
    qDebug()<<"currentIndex:"<<currentAPIndex<<"pBssList:"<<QString((char *)pBssEntry->dot11Ssid.ucSSID)<<endl;
    return (pBssEntry->dwFlags & 0x01);
}

bool wirelessControl::APHasProfile()
{
    if(!refleshEntry())
    {
        return false;
    }
    return ((pBssEntry->dwFlags & (0x01)<< 1) >> 1);
}

void wirelessControl::APDeleteProfile()
{
    WlanDisconnect(hClient,&pIfInfo->InterfaceGuid,NULL);
    WlanDeleteProfile(hClient,&pIfInfo->InterfaceGuid,pBssEntry->strProfileName,NULL);
}
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<结束>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<公有槽>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void wirelessControl::wireless_interface_changed(int i)
{
    currentWirelessIndex = i;
    updataSSIDList(i);
}

void wirelessControl::wireless_SSID_changed(int i)
{
    currentAPIndex = i;
    pBssEntry = (WLAN_AVAILABLE_NETWORK *) &pBssList->Network[i];
    currentSSID = QString::fromUtf8((char*)pBssEntry->dot11Ssid.ucSSID);
}

QStringList wirelessControl::get_ssid_list(void)
{
	qDebug()<<"currentIndex:"<<currentAPIndex<<"pBssList:"<<QString((char *)pBssEntry->dot11Ssid.ucSSID);
    return this->SSIDList;
}
