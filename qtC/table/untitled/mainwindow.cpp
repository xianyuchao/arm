#include "mainwindow.h"
#include "ui_mainwindow.h"





MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    QTableWidget *tableWidget = new QTableWidget(ui->textBrowser);


       tableWidget->setRowCount(16);//设置行数为

       tableWidget->setColumnCount(16);//设置列数为

       tableWidget->setGeometry(QRect(0,0,600,600));//设置tableWidget的大小


       //tableWidget->setItem(0,0,new QTableWidgetItem("abc"));//第一行第一列的内容设置为abc

      // tableWidget->setItem(1,0,new QTableWidgetItem("def"));//第二行第一列的内容设置为abc



    //tableWidget->setFixedWidth(50);
    //tableWidget->setFixedHeight(50);

/*
       tableWidget->setColumnWidth(0,40);//设置第一列的列宽

       tableWidget->setColumnWidth(1,110);//设置第二列的列宽

       tableWidget->setColumnWidth(2,100);//设置第三列的列宽

       tableWidget->setColumnWidth(3,60);//设置第四列的列宽

       tableWidget->setColumnWidth(4,85);//设置第五列的列宽*/


       //QTextCodec::setCodecForTr(QTextCodec::codecForName("GB18030"));//编码设置为GB18030
        //QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));//编码设置为
   // 列表的标题----车次 车牌 支付卡 金额 累计金额


        unsigned char temp[256];

       QStringList qs1=QStringList();
       for(int i=0;i<16;i++)
       {


           QString str;
            str.setNum(i);
            str='0'+str;
            str=str.right(2);

           qs1.append( str);
       }
       tableWidget->setHorizontalHeaderLabels(qs1);
       tableWidget->setVerticalHeaderLabels(qs1);

       for(int i=0;i<16;i++)
       {
           for(int j=0;j<16;j++)
           {
               QString str;
                str.setNum(temp[i*16+j]);
                str='0'+str;
                str=str.right(2);


               tableWidget->setItem(i,j,new QTableWidgetItem(str));//第二行第一列的内容设置为

           }

       }


       //tableWidget->setHorizontalHeaderLabels(QStringList() <<tr("车次")<<tr("车牌")<<tr("支付卡")<<tr("金额")<<tr("累计金额"));
       //tableWidget->setFont(QFont("wenquanyi",12,3));//设置字体

       //tableWidget->setVerticalHeaderLabels(QStringList() <<tr("车次")<<tr("车牌")<<tr("支付卡")<<tr("金额")<<tr("累计金额"));
       //tableWidget->setFont(QFont("wenquanyi",12,3));//设置字体

       //QHeaderView* headerView = tableWidget->verticalHeader();
       //headerView->setHidden(true); //行名隐藏
       tableWidget->resizeColumnsToContents();
       tableWidget->resizeRowsToContents();

}

MainWindow::~MainWindow()
{
    delete ui;
}
