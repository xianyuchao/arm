#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    sender=new QUdpSocket(0);

    for(int i=0;i<2000;i++)
    {
        if(sender->bind(QHostAddress::Null, i+TARGETHOSTPORT) == true)  // 绑定端口,7001 开始
        {

            ui->label_2->setText(QString::number(i+TARGETHOSTPORT));
            connect(sender, SIGNAL(readyRead()),this, SLOT(readPendingDatagrams()));
            break;
        }
        if(TARGETHOSTPORT+2000<=i) // 申请不到端口，退出程序
        {
            //exit ;
        }
    }



    longerList = (QStringList() << "1287370402" << "1287370388" );
    ui->comboBox->addItems(longerList);


    connect(&m_timer, SIGNAL(timeout()), SLOT(timeout()) );//5 秒1个心跳包
    m_timer.start(5000);
}

MainWindow::~MainWindow()
{
    delete ui;
}


//f=1&d=1287370388&m=1234567890&z=XXX&from=sb->server
//心跳包
void MainWindow::heartbreak(float state)
{
    QString out;
    state=state;

    out.clear();

    out+="f=1&d=";
    out+=ui->comboBox->currentText();
    out+="&m=";
    out+=DEVPASSWORD;
    out+="&z=";
    out+=QString::number(state,'f',2);
    out+="&from=sb->server";

   // qDebug()<<out;
    sendUDP(out.toLatin1());
}


//命令返回包
void MainWindow::cmdback(float state)
{
    QString out;
    state=state;

    out.clear();

    out+="f=b&d=";
    out+=device;
    out+="&m=";
    out+=DEVPASSWORD;
    out+="&n=";
    out+=account;
    out+="&com=";
    out+=command;
    out+="&from=sb->server";

   // qDebug()<<out;
    sendUDP(out.toLatin1());
}

//f=a&d=1287369152&n=lovfelife&com=open&from=server->sb
//命令格式
QString MainWindow::getcmd(QString str)
{
    QStringList ql=str.split("&");//将字符串以“；”为界分割成数组形式存到QStringList变量strlist中
    ui->listWidget->clear();
    ui->listWidget->addItems(ql);
    QStringList subql=ql.at(3).split("=");


    subql=ql.at(0).split("=");
    QString type=subql.at(1);

    if(type=="1")// 心跳包
        return NULL;

    qDebug()<<str;// 心跳包不输出调试信息

    if(type=="a")// 控制命令
    {
        subql=ql.at(1).split("=");
        device=subql.at(1);

        subql=ql.at(2).split("=");
        account=subql.at(1);

        command=subql.at(1);

        if(command=="open")
        {
            ui->label->setText("open");
        }
        if(command=="close")
        {
            ui->label->setText("close");
        }

        ui->label->setText(subql.at(1));
        cmdback(1);
    }


    return subql.at(1);

}

void MainWindow::sendUDP(QByteArray datagram)
{
    QHostAddress serverAddress = QHostAddress(TARGETHOST);
    sender->writeDatagram(datagram.data(), datagram.size(),serverAddress, TARGETHOSTPORT);

}

void MainWindow::readPendingDatagrams(void)
{
    QByteArray datagram;

    while (sender->hasPendingDatagrams()) {

    datagram.resize(sender->pendingDatagramSize());
    sender->readDatagram(datagram.data(), datagram.size());

    //ui->textEdit->setPlainText(datagram);
    //qDebug()<<datagram;



    }
    getcmd(QString(datagram));
}

void MainWindow::on_pushButton_clicked()
{
    heartbreak(1120.5123);
}

void MainWindow::timeout()
{
    heartbreak(1120.5123);
}
