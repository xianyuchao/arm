#ifndef SERIAL_H
#define SERIAL_H

#include <QDialog>
#include <QSerialPort>
#include <QSerialPortInfo>

typedef struct
{
    QString portName;
    int baud;
    int parity;
    int dataBits;
    int stopBits;
} SERIAL_ATTR_T;

namespace Ui {
class Serial;
}

class Serial : public QDialog
{
    Q_OBJECT

public:
    explicit Serial(QWidget *parent = 0);
    ~Serial();
    void execute();
    bool opens();
    bool isOpen();
    void closes();
    void setAttr(SERIAL_ATTR_T &attr);
    int write(QByteArray data);
    QString errorStr();

private:
    QSerialPort *port;
    SERIAL_ATTR_T attr;

signals:
    void SerialSetingSignal(SERIAL_ATTR_T &attr);

private slots:
    void on_pushButton_Switch_clicked();

private:
    Ui::Serial *ui;
};

#endif // SERIAL_H
