#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QUdpSocket>
#include <QDateTime>
//#include <QHostInfo>
#include <QtNetwork/QHostInfo>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QDateTime GetNetworkTime(char* time_str);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
