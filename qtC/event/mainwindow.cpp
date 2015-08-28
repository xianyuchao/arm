#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
//#include <QEvent>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QWheelEvent>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->verticalSlider->setPageStep(1);
    //ui->verticalSlider->wheelEvent(QWheelEvent *event);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::keyPressEvent(QKeyEvent * event)

{

    switch (event->key()) {

    case Qt::Key_Plus:
        qDebug("keyPressEvent:+");
        //zoomIn();

        break;

    case Qt::Key_Minus:
        qDebug("keyPressEvent:-");
        //zoomOut();

        break;

    case Qt::Key_Left:
        qDebug("keyPressEvent:left");
        // …
        break;
    default:
        //MainWindow::keyPressEvent(event);
        break;
    }

}

void MainWindow::mousePressEvent(QMouseEvent*e)
{
    if(e->button()==Qt::LeftButton)
    {
        qDebug("mousePressEvent:x:%d,y:%d",e->globalX(),e->globalY());
    }
}

void MainWindow::wheelEvent(QWheelEvent *event)
 {
     int numDegrees = event->delta() / 8;//滚动的角度，*8就是鼠标滚动的距离
     int numSteps = numDegrees / 15;//滚动的步数，*15就是鼠标滚动的角度

     qDebug("wheelEvent:%d DEG,%d STEP",numDegrees,numSteps);

     if (event->orientation() == Qt::Horizontal) {
         //scrollHorizontally(numSteps);       //水平滚动
         qDebug("hor");
     } else {
         //scrollVertically(numSteps);       //垂直滚动

         int i=ui->verticalSlider->value();
         if(numDegrees>0)
             i++;
         else
             i--;
         ui->verticalSlider->setValue(i);

         //void	setTickPosition(TickPosition position)
         qDebug("ver");
     }

     //event->accept();      //接收该事件
     event->ignore();
 }



void MainWindow::on_verticalSlider_valueChanged(int value)
{
    QString str;
    ui->label->setText(str.setNum(value,10));
}
