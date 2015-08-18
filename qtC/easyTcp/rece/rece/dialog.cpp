#include "dialog.h"
#include "ui_dialog.h"

#include <QtNetwork>
#include <qdebug.h>

QTcpServer *server;
QTcpSocket *clientConnection;

void Dialog::acceptConnection()
{
    clientConnection = server->nextPendingConnection();

    connect(clientConnection, SIGNAL(readyRead()), this, SLOT(readClient()));

    //qDebug() << "Date:" << QDate::currentDate()<<"accept Connection";

}
void Dialog::readClient()
{
    QString str = clientConnection->readAll();
    //或者
    //char buf[1024];
    //clientConnection->read(buf,1024);

    //ui->textEdit->setPlainText(str);
    ui->textEdit->append(str);

    // qDebug() << "Date:" << QDate::currentDate()<<"read client";
}


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);


    ui->textEdit->setPlainText("buf");

    server = new QTcpServer();
    c_port=6665;
    server->listen(QHostAddress::Any, c_port);
    connect(server, SIGNAL(newConnection()), this, SLOT(acceptConnection()));


}

Dialog::~Dialog()
{
    delete ui;
}



void Dialog::on_lineEdit_textChanged(const QString &arg1)
{
    //qDebug()<<arg1;
    int port=arg1.toInt();
    //qDebug()<<port;
    if(port!=0)
    {
        c_port=port;
        server->close();
        server->listen(QHostAddress::Any, c_port);
    }
}

void Dialog::on_pushButton_clicked()
{
    ui->textEdit->setPlainText("");
}

void Dialog::updateLabel(void)
{
    //ui->
}
