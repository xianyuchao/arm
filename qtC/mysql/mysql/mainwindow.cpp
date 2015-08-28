#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <qdebug.h>

#include <QSqlDatabase>
#include <QSqlQuery>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //输出可用数据库
    qDebug()<<"available drivers:";
    QStringList drivers = QSqlDatabase::drivers();
    //foreach(QString driver, drivers)
        //qDebug()<<driver;

    //打开MySQL
    QSqlDatabase data_base = QSqlDatabase::addDatabase("QMYSQL");
    data_base.setHostName("localhost");  //设置主机地址
    data_base.setPort(3306);  //设置端口
    data_base.setDatabaseName("test");  //设置数据库名称
    data_base.setUserName("root");  //设置用户名
    data_base.setPassword("123456");  //设置密码
    if(!data_base.open())
        qDebug()<<"failed to connect to mysql";
    else
        qDebug()<<"success";

    QSqlQuery query;
    int numrows = 0;
    query.exec("select * from MyClass");
    while(query.next())
    {
        int id = query.value(0).toInt();
        id=id;
        QString name = query.value(1).toString();
        //qDebug()<<name;
        int age = query.value(2).toInt();
        age=age;
        //qDebug()<<age;
        //ui->listWidget->insertItem(numrows,QString::number(id) +"\t"+ name + "\t"+ QString::number(age));
        numrows++;

        qDebug()<<query.value(0).toInt()<<"  "<<query.value(1).toString();
    }
    query.exec("INSERT INTO `test`.`myclass` (`name`) VALUES ('333');");
}

MainWindow::~MainWindow()
{
    delete ui;
}
