#include "mypainterwidget.h"
#include <QString>
#include <QMessageBox>
#include <QPainter>
#include <QPen>
#include <QMouseEvent>


#include <QDebug>


#include "img.h"



MyPainterWidget::MyPainterWidget(QWidget* parent)
     :QWidget(parent){
    setMinimumSize(800,600);
    setMaximumSize(800,600);

    T1=new QTimer(this);
    connect(T1,SIGNAL(timeout()),this,SLOT(update()));

    T1->start(10);

    //this->setMouseTracking(true);


    //uchar *x;
    //x=(uchar *)Font_code;
   // font=(uchar *)Font_code;

    //unsigned char *p=(uchar *)Font_code;
    //p=(uchar *)Font_code;
    //font=Font_code[0];

    qDebug()<<"ok"<<endl;
}

MyPainterWidget::~MyPainterWidget(){

}

#define STARTX  100     //坐标0位置
#define STARTY  100

#define PIXELSIZE   4//缩放比例因子

#define XWIDTHPYS   84//实际尺寸
#define YWIDTHPYS   48//实际尺寸

#define XWIDTH  XWIDTHPYS*PIXELSIZE//缩放后尺寸
#define YWIDTH  YWIDTHPYS*PIXELSIZE

#define BACKCOLOR   Qt::white//背景色
#define FRONTCOLOR   Qt::black//前景色

uchar mem[YWIDTHPYS/8][XWIDTHPYS];//6*84

void putCh(uchar ascii)
{
    int x=27;
    for(int i=0;i<6;i++)
    {
        mem[4][x++]=Font_code[ascii][i];
    }
}

void putImg(void)
{
    for(int i=0;i<6;i++)
    {
        for(int j=0;j<84;j++)
        {
            mem[i][j]=    pic[i*84+j];
        }
    }

}

void putPic(int start)
{
    for(int i=0;i<84;i++)
    {
        for(int j=0;j<5;j++)
        {
            mem[j][i]=    img1[start+i*5+j];
        }

    }

}

void MyPainterWidget::paintEvent(QPaintEvent*p){
    p=p;
    QPainter painter(this);
    QPen pen;                                 //创建一个画笔
    pen.setWidth(PIXELSIZE);
    painter.setPen(pen);

    static int st=0;
    st+=5;
if(st>=640*5-84*5)st=0;
    //mem[2][3]=0x4d;
    //mem[5][21]=0x54;

    //putCh(11);
    //putImg();
    putPic(st);

    int x=STARTX,y=STARTY;
    uchar mask;

    for(int posx=0;posx<XWIDTHPYS;posx++)
    {
        for(int posy=0;posy<YWIDTHPYS/8;posy++)
        {
            mask=0x01;
            for(int j=0;j<8;j++)
            {
                if(mask & mem[posy][posx])
                {
                    pen.setColor(FRONTCOLOR);
                    painter.setPen(pen);
                    painter.drawPoint(x,y);

                }else
                {
                    pen.setColor(BACKCOLOR);
                    painter.setPen(pen);
                    painter.drawPoint(x,y);
                }
                mask<<=1;
                y+=PIXELSIZE;
            }

        }
        x+=PIXELSIZE;
        y=STARTY;
    }
    /*
    for(int i=0;i<6;i++)
    {
        mask=0x01;

        for(int j=0;j<8;j++)
        {
            if(mask & Font_code[ch][i])
            {
                pen.setColor(FRONTCOLOR);
                painter.setPen(pen);
                painter.drawPoint(x,y);

            }else
            {
                pen.setColor(BACKCOLOR);
                painter.setPen(pen);
                painter.drawPoint(x,y);
            }
            mask<<=1;
            y+=4;

        }
        qDebug("%x",(char)Font_code[ch][i]);
        x+=4;
        y=100;
    }*/


}

void MyPainterWidget::mousePressEvent(QMouseEvent *e){
    e=e;
#if 0
    QPainter painter(this);
    QPen pen;                                 //创建一个画笔
    pen.setColor(Qt::darkCyan);
    pen.setWidth(5);
    painter.setPen(pen);
#endif



    /*
    setCursor(Qt::PointingHandCursor);
    startPnt = e->pos();
    endPnt = e->pos();
    this->isPressed = true;
    //QString msg ="("+QString::number(e->x())+","+QString::number(e->y())+")";
    //QMessageBox::warning(this,tr("Warning"),msg,QMessageBox::Ok);*/
}

void MyPainterWidget::mouseMoveEvent(QMouseEvent *e){
    e=e;
    /*if(this->isPressed){
        endPnt = e->pos();

        myLine* line = new myLine;  //put the new line into vector
        line->startPnt = startPnt;
        line->endPnt = endPnt;
        this->lines.push_back(line);

        update();                                    //repainter，call paintEvent
        startPnt = endPnt;
    }*/
}

void MyPainterWidget::mouseReleaseEvent(QMouseEvent *e){
    e=e;
    //setCursor(Qt::ArrowCursor);
    //this->isPressed = false;
}

