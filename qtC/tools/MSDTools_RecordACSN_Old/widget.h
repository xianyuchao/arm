#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QString>
#include <QStringList>
#include <QMessageBox>
#include <QPixmap>
#include <QTimer>
#include <QTime>
#include <QSound>

#include <windows.h>

#include "wirelesscontrol.h"
#include "hatcp.h"
#include "getsn.h"
#include "globalDefine.h"

#include "serial.h"

#include <QKeyEvent>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();



private slots:
    //void on_D2Edit_textChanged(const QString &arg1);
    void on_writeButton_clicked();
    void on_SNEdit_textChanged();

    void timeout_slot();
    void tcp_connect_success();
    void tcp_data_received();
    void tcp_error_occured(int index);
    void check_interface();
    void date_no_receive_timeout();
    void on_aboutButton_clicked();
    //void on_D2Edit_returnPressed();
    void on_SNEdit_returnPressed();
    //void on_moduleSelectButton_clicked();
    void on_SNSelectButton_clicked();
    void on_reWriteCheckBox_clicked(bool checked);

    void on_aboutButtonSerial_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void removeSameSNList();

    void timerMisc();

private:
    Ui::Widget *ui;

    bool checkInput();

    void SSIDDisconnectedDisplay();
    void SSIDConnectingDisplay();
    void SSIDConnectedDisplay();
    void SSIDReadyDisplay();

    bool connectSSID();
    void connectTCP();

    unsigned char CRC8(unsigned char in,unsigned char crc);

    QVector<unsigned char> SNReport();
    QVector<unsigned char> checkAnswerReport();

    void enableWidget(bool flag);
    void endWrite();

    //void get00SSID();
    void getACSSID();

    //void passSound();
    void errorSound();

    wirelessControl SSIDTest;
    HATcp TCPTest;
    QTimer timer;
    QTimer checkInterfaceTimer;
    QTimer checkSNSendTimer;

    int testCounter;
    int tcpCounter;
    int step;

    Serial *serial;

    void keyPressEvent(QKeyEvent * event); // 回车事件
    QStringList scanINSN;
};

#endif // WIDGET_H
