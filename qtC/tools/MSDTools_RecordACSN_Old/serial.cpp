#include "serial.h"
#include "ui_serial.h"
#include <QMessageBox>

Serial::Serial(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Serial)
{
    ui->setupUi(this);
    setFixedSize(size());

    ui->comboBox_Parity->setItemData(0, QSerialPort::NoParity);
    ui->comboBox_Parity->setItemData(1, QSerialPort::OddParity);
    ui->comboBox_Parity->setItemData(2, QSerialPort::EvenParity);
    attr.parity = ui->comboBox_Parity->itemData(ui->comboBox_Parity->currentIndex()).toInt();

    ui->comboBox_DataBits->setItemData(0, QSerialPort::Data8);
    ui->comboBox_DataBits->setItemData(1, QSerialPort::Data7);
    ui->comboBox_DataBits->setItemData(2, QSerialPort::Data6);
    ui->comboBox_DataBits->setItemData(3, QSerialPort::Data5);
    attr.dataBits = ui->comboBox_DataBits->itemData(ui->comboBox_DataBits->currentIndex()).toInt();

    ui->comboBox_StopBits->setItemData(0, QSerialPort::OneStop);
    ui->comboBox_StopBits->setItemData(1, QSerialPort::TwoStop);
    attr.stopBits = ui->comboBox_StopBits->itemData(ui->comboBox_StopBits->currentIndex()).toInt();

    port = new QSerialPort(this);
}

Serial::~Serial()
{
    delete ui;
}

void Serial::execute()
{
    /* 列出可用串口 */
    ui->comboBox_Com->clear();
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        if (info.isValid())
        {
            ui->comboBox_Com->addItem(info.portName());
            if (info.portName() == attr.portName)
            {
                ui->comboBox_Com->setCurrentIndex(ui->comboBox_Com->count() - 1);
            }
        }
    }

    /* 列出可用波特率 */
    ui->comboBox_Baud->clear();
    QString baud;
    foreach (const qint32 iBaud, QSerialPortInfo::standardBaudRates()) {
        ui->comboBox_Baud->addItem(baud.sprintf("%d", iBaud));
        if (iBaud == attr.baud)
        {
            ui->comboBox_Baud->setCurrentIndex(ui->comboBox_Baud->count() - 1);
        }
    }

    for (int i=0; i<ui->comboBox_Parity->count(); i++)
    {
        if (ui->comboBox_Parity->itemData(i).toInt() == attr.parity)
        {
            ui->comboBox_Parity->setCurrentIndex(i);
        }
    }

    for (int i=0; i<ui->comboBox_DataBits->count(); i++)
    {
        if (ui->comboBox_DataBits->itemData(i).toInt() == attr.dataBits)
        {
            ui->comboBox_DataBits->setCurrentIndex(i);
        }
    }

    for (int i=0; i<ui->comboBox_StopBits->count(); i++)
    {
        if (ui->comboBox_StopBits->itemData(i).toInt() == attr.stopBits)
        {
            ui->comboBox_StopBits->setCurrentIndex(i);
        }
    }

    if (port->isOpen())
    {
        ui->comboBox_Com->setEnabled(false);
        ui->comboBox_Baud->setEnabled(false);
        ui->comboBox_Parity->setEnabled(false);
        ui->comboBox_DataBits->setEnabled(false);
        ui->comboBox_StopBits->setEnabled(false);
    }
    else
    {
        ui->comboBox_Com->setEnabled(true);
        ui->comboBox_Baud->setEnabled(true);
        ui->comboBox_Parity->setEnabled(true);
        ui->comboBox_DataBits->setEnabled(true);
        ui->comboBox_StopBits->setEnabled(true);
    }

    if (ui->comboBox_Com->count() > 0 && ui->comboBox_Baud->count() > 0)
    {
        ui->pushButton_Switch->setEnabled(true);
    }
    else
    {
        ui->pushButton_Switch->setEnabled(false);
    }

    exec();
}

void Serial::on_pushButton_Switch_clicked()
{

    if (isOpen())
    {
        closes();
        ui->pushButton_Switch->setText("打开串口");
        ui->comboBox_Com->setEnabled(true);
        ui->comboBox_Baud->setEnabled(true);
        ui->comboBox_Parity->setEnabled(true);
        ui->comboBox_DataBits->setEnabled(true);
        ui->comboBox_StopBits->setEnabled(true);
    }
    else
    {
        attr.portName = ui->comboBox_Com->currentText();
        attr.baud = ui->comboBox_Baud->currentText().toInt();
        attr.parity = ui->comboBox_Parity->itemData(ui->comboBox_Parity->currentIndex()).toInt();
        attr.dataBits = ui->comboBox_DataBits->itemData(ui->comboBox_DataBits->currentIndex()).toInt();
        attr.stopBits = ui->comboBox_StopBits->itemData(ui->comboBox_StopBits->currentIndex()).toInt();

        /* 通知mainwindow将新设置的串口写入文件. */
        emit SerialSetingSignal(attr);

        if (opens())
        {
            ui->pushButton_Switch->setText("关闭串口");
            ui->comboBox_Com->setEnabled(false);
            ui->comboBox_Baud->setEnabled(false);
            ui->comboBox_Parity->setEnabled(false);
            ui->comboBox_DataBits->setEnabled(false);
            ui->comboBox_StopBits->setEnabled(false);
        }
        else
        {
            QMessageBox msgBox;
            QString msg("串口打开失败: ");
            msg.append(errorStr());
            msgBox.setText(msg);
            msgBox.exec();
        }
    }
}

bool Serial::opens()
{
    if (0 == attr.portName.count())
    {
        return false;
    }

    if (0 == attr.baud)
    {
        return false;
    }

    port->setPortName(attr.portName);

    if (false == port->open(QIODevice::ReadWrite))
    {
        return false;
    }

    port->setBaudRate(attr.baud);
    port->setParity((QSerialPort::Parity)attr.parity);
    port->setDataBits((QSerialPort::DataBits)attr.dataBits);
    port->setStopBits((QSerialPort::StopBits)attr.stopBits);
    port->setFlowControl(QSerialPort::NoFlowControl);

    return true;
}

bool Serial::isOpen()
{
    return port->isOpen();
}

void Serial::closes()
{
    port->close();
}

void Serial::setAttr(SERIAL_ATTR_T &attr)
{
    this->attr = attr;
    return;
}

int Serial::write(QByteArray data)
{
    return port->write(data);
}

QString Serial::errorStr()
{
    return port->errorString();
}
