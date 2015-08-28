#ifndef MYPAINTERWIDGET_H
#define MYPAINTERWIDGET_H

#include <QWidget>
#include <QPoint>
#include <vector>

#include<QTimer>

using namespace std;


//线段
typedef struct myLine{
    QPoint startPnt;
    QPoint endPnt;
}myLine;

class MyPainterWidget: public QWidget
{
public:
    MyPainterWidget(QWidget* parent);
    ~MyPainterWidget();

    //继承
    void paintEvent(QPaintEvent* p);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

    QPoint startPnt;   //起点
    QPoint endPnt;     //终点
    bool isPressed;    //鼠标是否按下

    vector<myLine*> lines; //存放所有的线段

    vector<QPoint*> points; //存放所有的线段

    unsigned char *font;

    QTimer *T1;
};




#endif // MYPAINTERWIDGET_H

