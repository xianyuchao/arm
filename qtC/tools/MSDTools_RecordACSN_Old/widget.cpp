#include "widget.h"
#include "ui_widget.h"
#include "file.h"

extern "C"
{
    #include "MDll.h"
}

#include <QInputDialog>

#include <QDebug>

//该函数无任何意义，仅调用一次AES_set_decrypt_key和AES_ecb_encrypt
void noUse()
{
    unsigned char out[AES_BLOCK_SIZE];
    AES_KEY theKey;
    AES_set_decrypt_key(out,8,&theKey);
    AES_ecb_encrypt(out,out,&theKey,AES_DECRYPT);
}

QMap <QString,int> qMapSn;//全局

QSound errorVoice(":/wav/error.wav");

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->SNEdit->setFocus();

    testCounter = 0;
    tcpCounter = 0;
    step = 0;
    connect(&timer,SIGNAL(timeout()),this,SLOT(timeout_slot()));
    //connect(&checkInterfaceTimer,SIGNAL(timeout()),this,SLOT(check_interface()));
    connect(&checkSNSendTimer,SIGNAL(timeout()),this,SLOT(date_no_receive_timeout()));

    connect(&TCPTest,SIGNAL(haveConnected()),this,SLOT(tcp_connect_success()));
    connect(&TCPTest,SIGNAL(error(int)),this,SLOT(tcp_error_occured(int)));
    connect(&TCPTest,SIGNAL(tcpArrived()),this,SLOT(tcp_data_received()));

    connect(&TCPTest,SIGNAL(udpArrived()),this,SLOT(removeSameSNList()));

    QTimer *readSNFromFile=new QTimer(this);
    connect(readSNFromFile,SIGNAL(timeout()),this,SLOT(timerMisc()));
    readSNFromFile->start(1000);// 1秒读1次

    //QTimer

    if(SSIDTest.getInterfaceList().isEmpty())
    {
        QMessageBox::information(this,tr("网卡设备错误"),tr("未发现无线网卡设备"));
        exit(0);
    }

    serial = new Serial(this);
    // qDebug()<<"初始化widget";
    //ui->listWidget->addItem("wifi1");
    ui->listWidget->addItems(SSIDTest.getSSIDList());
    ui->label->setText("当前网络:"+SSIDTest.currentSSID);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::SSIDDisconnectedDisplay()
{
    QByteArray msg("FBCE");
    serial->write(msg);

    errorSound();
    ui->ledLabel->setPixmap(QPixmap(":/img/img/red.png"));
    ui->BackgroundLabel->setPixmap(QPixmap(":/img/img/redB.png"));
    //QCoreApplication::processEvents();
}

void Widget::SSIDConnectedDisplay()
{
    QByteArray msg("FACE");
    serial->write(msg);

    ui->ledLabel->setPixmap(QPixmap(":/img/img/green.png"));
    ui->BackgroundLabel->setPixmap(QPixmap(":/img/img/greenB.png"));
}

void Widget::SSIDReadyDisplay()
{
    ui->ledLabel->setPixmap(QPixmap(":/img/img/red.png"));
    ui->BackgroundLabel->setPixmap(QPixmap(":/img/img/redB.png"));
}

void Widget::SSIDConnectingDisplay()
{
    ui->ledLabel->setPixmap(QPixmap(":/img/img/yellow.png"));
    ui->BackgroundLabel->setPixmap(QPixmap(":/img/img/yellowB.png"));
}

//开始按钮
void Widget::on_writeButton_clicked()
{
    if(!checkInput())
    {
        return;
    }

    QByteArray msg("FCCE");
    serial->write(msg);

    SSIDConnectingDisplay();
    ui->theStateLabel->setText(tr("正在查询SSID...."));
    //QCoreApplication::processEvents();

    if(connectSSID())
    {
        enableWidget(false);
        SSIDConnectingDisplay();
        ui->theStateLabel->setText(tr("正在连接SSID...."));
    }
}

//第一步、连接网卡
bool Widget::connectSSID()
{
    int counter = 0;

    for(int i=0;i<SSIDAPPEAR_TIMES;i++)
    {
        SSIDTest.updataSSIDList(0);
        QCoreApplication::processEvents();// 1


        if(SSIDTest.findSSID(ui->SSIDEdit->text()) < 0)
        {
            counter++;
            if(counter == SSIDAPPEAR_TIMES)
            {
                SSIDDisconnectedDisplay();
                ui->theStateLabel->setText(tr("未找到SSID信号"));
                endWrite();
                return false;
            }
            qDebug()<<"connecti:"<<i<<endl;
            //Sleep(WAIT_SSIDAPPEAR_TIME);
            QCoreApplication::processEvents();
        }
        else
        {
            SSIDTest.wlanConnectInterface(ui->SSIDEdit->text(),MODULE_DEFAULT_PSW);
            timer.setSingleShot(false);
            timer.start(WAIT_APCONNECT_TIME);
            return true;
        }
    }
    return false;
}

unsigned char Widget::CRC8(unsigned char in, unsigned char crc)
{
    const uchar crctable[] =
    {
        0, 94,188,226, 97, 63,221,131,194,156,126, 32,163,253, 31, 65,
        157,195, 33,127,252,162, 64, 30, 95, 1,227,189, 62, 96,130,220,
        35,125,159,193, 66, 28,254,160,225,191, 93, 3,128,222, 60, 98,
        190,224, 2, 92,223,129, 99, 61,124, 34,192,158, 29, 67,161,255,
        70, 24,250,164, 39,121,155,197,132,218, 56,102,229,187, 89, 7,
        219,133,103, 57,186,228, 6, 88, 25, 71,165,251,120, 38,196,154,
        101, 59,217,135, 4, 90,184,230,167,249, 27, 69,198,152,122, 36,
        248,166, 68, 26,153,199, 37,123, 58,100,134,216, 91, 5,231,185,
        140,210, 48,110,237,179, 81, 15, 78, 16,242,172, 47,113,147,205,
        17, 79,173,243,112, 46,204,146,211,141,111, 49,178,236, 14, 80,
        175,241, 19, 77,206,144,114, 44,109, 51,209,143, 12, 82,176,238,
        50,108,142,208, 83, 13,239,177,240,174, 76, 18,145,207, 45,115,
        202,148,118, 40,171,245, 23, 73, 8, 86,180,234,105, 55,213,139,
        87, 9,235,181, 54,104,138,212,149,203, 41,119,244,170, 72, 22,
        233,183, 85, 11,136,214, 52,106, 43,117,151,201, 74, 20,246,168,
        116, 42,200,150, 21, 75,169,247,182,232, 10, 84,215,137,107, 53
    };

    in ^= crc;
    crc = crctable[in];
    return  crc;
}


void Widget::on_SNEdit_textChanged()
{
    if(!ui->SNEdit->text().isEmpty())
    {
        if(ui->SNEdit->text().remove(20,ui->SNEdit->text().size()-20) == "http://www.midea.com" && ui->SNEdit->text().size() == CODE2SIZT)
        {
            //截取SN
            QString text = ui->SNEdit->text();
            text.remove(0,text.size() - SNSTRSIZT);
            ui->SNEdit->setText(text);
        }
        else if(ui->SNEdit->text().at(0) == 'D' && ui->SNEdit->text().size() == SNSTRSIZT)
        {
            ui->writeButton->setFocus();
            ui->writeButton->setDefault(true);
            getACSSID();
            ui->theStateLabel->setText(tr("停止"));
            //}
            if(!ui->gunCheckBox->isChecked())
            {
                on_writeButton_clicked();
            }
        }
        else
        {
            SSIDReadyDisplay();
            ui->theStateLabel->setText(tr("停止"));
        }
    }
    else
    {
        SSIDReadyDisplay();
        ui->theStateLabel->setText(tr("停止"));
    }
}

bool Widget::checkInput()
{
    QString ssid = ui->SSIDEdit->text();
    if(ssid.isEmpty())
    {
        QMessageBox::information(this,tr("SSID错误"),tr("模块信息错误！，无法生成SSID！"));
        return false;
    }
    else
    {
        QStringList ssidStrList = ssid.split("_");
        if(ssidStrList.size() != 3)
        {
            QMessageBox::information(this,tr("SSID错误"),tr("SSID格式错误！"));
            return false;
        }
        if(ssidStrList.at(0) != "midea")
        {
            QMessageBox::information(this,tr("SSID错误"),tr("SSID品牌不为midea！"));
            return false;
        }
        if(!(ssidStrList.at(1) == "00" || ssidStrList.at(1) == "ac"))
        {
            QMessageBox::information(this,tr("SSID错误"),tr("SSID类型不为00或ac！"));
            return false;
        }
        if(ssidStrList.at(2).size() != 4)
        {
            QMessageBox::information(this,tr("SSID错误"),tr("SSID长度错误！"));
            return false;
        }
        if(ui->SNEdit->text().at(0) != 'D')
        {
            QMessageBox::information(this,tr("SN错误"),tr("空调SN格式错误！"));
            return false;
        }
    }
    if(ui->SNEdit->text().size() != SNSTRSIZT)
    {
        QMessageBox::information(this,tr("SN错误"),tr("SN长度错误！"));
        return false;
    }
    return true;
}

void Widget::tcp_error_occured(int index)
{
    switch (index)
    {
    case 0:
        //QMessageBox::information(this,tr("TCP错误"),tr("未知错误！"));
        ui->theStateLabel->setText(tr("TCP未知错误！"));
        //printFailMes(tr("未知错误！"));
        break;
    case 1:
        //printFailMes(tr("无法建立TCP连接！"));
        //QMessageBox::information(this,tr("TCP错误"),tr("无法建立TCP连接！"));
        if(tcpCounter > TCP_CONNECT_TIMES)
        {
            ui->theStateLabel->setText(tr("无法建立TCP连接！"));
            tcpCounter = 0;
        }
        else
        {
            tcpCounter++;
            Sleep(TCP_DELAY_TIME);
            TCPTest.startConnect(AP_DEFAULT_IP,TCP_DEFAULT_PORT);
        }
        break;
    case 2:
        //printFailMes(tr("数据包长度错误！"));
        //QMessageBox::information(this,tr("TCP错误"),tr("数据包长度错误！"));
        ui->theStateLabel->setText(tr("TCP数据包长度错误！"));
        break;
    case 3:
        //QMessageBox::information(this,tr("TCP错误"),tr("数据包长度与报文标注不同！"));
        //printFailMes(tr("数据包长度与报文标注不同！"));
        ui->theStateLabel->setText(tr("TCP数据包长度与报文标注不同！"));
        break;
    case 5:
        //printMes(tr("\n\nTCP连接丢失\n"));
        //QMessageBox::information(this,tr("TCP错误"),tr("TCP连接丢失!"));
        ui->theStateLabel->setText(tr("TCP连接丢失!"));
        break;
    default:
        ui->theStateLabel->setText(tr("TCP未知错误!"));
        break;
    }
    SSIDDisconnectedDisplay();
    endWrite();
}

void Widget::date_no_receive_timeout()
{
    checkSNSendTimer.stop();
    SSIDDisconnectedDisplay();
    switch(step)
    {
    case 0:
        ui->theStateLabel->setText(tr("SN发送不成功!"));
        break;
    case 1:
        ui->theStateLabel->setText(tr("SN写入不成功!"));
        break;
    default:
        break;
    }
    endWrite();
}

void Widget::tcp_connect_success()
{
    tcpCounter = 0;
    SSIDConnectingDisplay();
    ui->theStateLabel->setText(tr("TCP连接成功!"));
    SSIDConnectingDisplay();
    ui->theStateLabel->setText(tr("正在发送SN!"));
    checkSNSendTimer.setSingleShot(false);
    checkSNSendTimer.start(WAIT_RECORD_ANSWER_TIME);
}

void Widget::tcp_data_received()
{
    QVector<unsigned char> report;
    QString reportStr;

    report = TCPTest.getDate();

    switch(step)
    {
    case 0:
        break;
    case 1:
        break;
    default:
        break;
    }
}

void Widget::timeout_slot()
{
    if(!SSIDTest.APIsConnected())
    {
        testCounter ++;
        if(testCounter > WAIT_APCONNECT_TIMES * APCONNECT_TIMES)
        {
            timer.stop();
            testCounter = 0;
            ui->theStateLabel->setText(tr("无法连接到SSID信号!"));
            //endTest();
            SSIDDisconnectedDisplay();
            endWrite();
            return;
        }
        else
        {
            if((testCounter % WAIT_APCONNECT_TIMES) == (WAIT_APCONNECT_TIMES - 1))
            {
                SSIDTest.wlanConnectInterface(ui->SSIDEdit->text(),MODULE_DEFAULT_PSW);
            }
        }
    }
    else
    {
        timer.stop();
        testCounter = 0;
        SSIDConnectedDisplay();
        ui->theStateLabel->setText(tr("SSID信号连接成功!"));
        endWrite();
    }
}

void Widget::enableWidget(bool flag)
{
    ui->writeButton->setEnabled(flag);
    ui->SNEdit->setEnabled(flag);
}

void Widget::endWrite()
{
    enableWidget(true);
    if(SSIDTest.APIsConnected())
    {
        checkInterfaceTimer.stop();//停止检查ssid定时器
    }
    ui->SNEdit->setFocus();
    ui->SNEdit->selectAll();
    if(SSIDTest.APHasProfile())
    {
        SSIDTest.APDeleteProfile();
    }
    step = 0;
}

void Widget::getACSSID()
{
    QString ssid = "midea_ac_";
    QString back = ui->SNEdit->text();
    back.remove(0,SNSTRSIZT - 4);
    ssid += back;
    ui->SSIDEdit->setText(ssid);
}

void Widget::errorSound()
{
    //errorVoice.play();
    //QSound::play("./wav/error.wav");
    //QSound::play("D:/error.wav");
}

void Widget::check_interface()
{
    if(!SSIDTest.APIsConnected())
    {
        ui->theStateLabel->setText(tr("SSID信号断开!"));
        SSIDDisconnectedDisplay();
        endWrite();
        checkInterfaceTimer.stop();
    }
}

void Widget::on_aboutButton_clicked()
{
    QMessageBox::about(this,tr("关于"),
                       tr("<h2>产线WIFI检测工具(家用空调)</h2>"
                          "<h3>美的集团智慧家居研究院</h3>"
                          "<p>开发作者:Zachary Chou"
                          "<p>更新日期:2015.05.04(M150417TC)"));
}

void Widget::on_SNEdit_returnPressed()
{
    if(ui->gunCheckBox->isChecked())
    {
        ui->writeButton->setFocus();
        ui->writeButton->setDefault(true);
    }
}

void Widget::on_SNSelectButton_clicked()
{
    ui->SNEdit->setFocus();
    ui->SNEdit->selectAll();
}

void Widget::on_reWriteCheckBox_clicked(bool checked)
{
    checked=checked;
    ui->SNEdit->setFocus();
    ui->SNEdit->selectAll();
    getACSSID();
}

void Widget::on_aboutButtonSerial_clicked()
{
    serial->execute();
}

void Widget::on_pushButton_2_clicked()// 连接按钮
{
    //SSIDTest.wlanConnectInterface(QString("wifitest"),QString("onlyfortest"));
    bool isOK;
    if(ui->listWidget->currentItem()==NULL)
    {
        qDebug()<<"exit";
        return;
    }
    QString selectSSID= ui->listWidget->currentItem()->text();
    QString text = QInputDialog::getText(NULL, "Input password",
                                         selectSSID,
                                         QLineEdit::Normal,
                                         "12345678",
                                         &isOK);
    if(isOK)
    {
        /*
           QMessageBox::information(NULL, "Information",
                                               "Your comment is: <b>" + text + "</b>",
                                               QMessageBox::Yes | QMessageBox::No,
                                               QMessageBox::Yes);*/
        SSIDTest.wlanConnectInterface(selectSSID,text);
        // if(true==SSIDTest.refleshEntry())
        {
            // ui->label->setText("当前网络:%s",SSIDTest.currentSSID);
        }
    }
}

void Widget::on_pushButton_clicked()// 刷新按钮
{
    //SSIDTest.getInterfaceList();
    ui->listWidget->clear();
    ui->listWidget->addItems(SSIDTest.getSSIDList());
    ui->label->setText("当前网络:"+SSIDTest.currentSSID);
}


void Widget::keyPressEvent(QKeyEvent * event)
{
    event=event;
    return;
#if 0
    //qDebug()<<event->key();
    switch (event->key()) {

    case Qt::Key_Return:
        // qDebug("keyPressEvent:0d 0a");

        // scanINSN.append(ui->SNEdit->text());
        if(ui->SNEdit->text().count()>4)
        {
            ui->SNList->addItem(ui->SNEdit->text());
        }
        ui->SNEdit->clear();
        break;

    default:
        //qDebug("aa");
        //MainWindow::keyPressEvent(event);
        break;
    }
#endif
}

void Widget::removeSameSNList(void)
{
    QByteArray datagram = TCPTest.getudpdatagram();
    QString SN;

    unsigned char buffer[1024] = {0};

    int i = 0;
    foreach (char byte, datagram) {
        buffer[i] = (unsigned char)byte;
        i++;
    }

    int res = Decrypt(buffer);

    if (res >= 0)
    {
        buffer[23] = 0;
        buffer[46] = 0;
        SN.append((char*)&buffer[24]);
    }

    /* TBD */

//qDebug()<<"1 "+datagram;
//QMap<QString,int>::iterator it=qMapSn.begin();
//qDebug()<<"2 "+it.key();
    if(qMapSn.contains(datagram)){//正常使用datagram 换为 SN

        //qDebug()<<"already exist"+lineStr;
        qMapSn.remove(datagram);
    }

}


void Widget::timerMisc(void)
{
    int i=0;

    readSN();


    ui->SNList->clear();
    QMap<QString,int>::iterator it;

    for ( it = qMapSn.begin(); it != qMapSn.end(); ++it ) {
            //qDebug( "%s: %s", it.key().ascii(), it.data().ascii()); //用key()和data()分别获取“键”和“值”

        ui->SNList->addItem(it.key());
        if( it.value()<SNTIMEOUT)
        {
            it.value()++;
        }
        if(it.value()>=SNTIMEOUT)
        {
               ui->SNList->item(i)->setBackgroundColor(ALARM_COLOR);
        }
//qDebug()<<it.value().second();

                i++;
            }


}
