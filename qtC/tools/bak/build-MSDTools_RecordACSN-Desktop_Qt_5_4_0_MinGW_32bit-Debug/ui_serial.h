/********************************************************************************
** Form generated from reading UI file 'serial.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERIAL_H
#define UI_SERIAL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Serial
{
public:
    QGroupBox *groupBox;
    QLabel *label_5;
    QLabel *label_4;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_6;
    QComboBox *comboBox_Com;
    QComboBox *comboBox_Baud;
    QComboBox *comboBox_Parity;
    QComboBox *comboBox_DataBits;
    QComboBox *comboBox_StopBits;
    QPushButton *pushButton_Switch;

    void setupUi(QDialog *Serial)
    {
        if (Serial->objectName().isEmpty())
            Serial->setObjectName(QStringLiteral("Serial"));
        Serial->resize(261, 311);
        groupBox = new QGroupBox(Serial);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(20, 10, 221, 241));
        groupBox->setAlignment(Qt::AlignCenter);
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(20, 190, 51, 31));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(20, 150, 51, 31));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 30, 51, 31));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(20, 70, 51, 31));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(20, 110, 51, 31));
        comboBox_Com = new QComboBox(groupBox);
        comboBox_Com->setObjectName(QStringLiteral("comboBox_Com"));
        comboBox_Com->setGeometry(QRect(90, 31, 111, 31));
        comboBox_Baud = new QComboBox(groupBox);
        comboBox_Baud->setObjectName(QStringLiteral("comboBox_Baud"));
        comboBox_Baud->setGeometry(QRect(90, 70, 111, 31));
        comboBox_Parity = new QComboBox(groupBox);
        comboBox_Parity->setObjectName(QStringLiteral("comboBox_Parity"));
        comboBox_Parity->setGeometry(QRect(90, 110, 111, 31));
        comboBox_DataBits = new QComboBox(groupBox);
        comboBox_DataBits->setObjectName(QStringLiteral("comboBox_DataBits"));
        comboBox_DataBits->setGeometry(QRect(90, 150, 111, 31));
        comboBox_StopBits = new QComboBox(groupBox);
        comboBox_StopBits->setObjectName(QStringLiteral("comboBox_StopBits"));
        comboBox_StopBits->setGeometry(QRect(90, 190, 111, 31));
        pushButton_Switch = new QPushButton(Serial);
        pushButton_Switch->setObjectName(QStringLiteral("pushButton_Switch"));
        pushButton_Switch->setGeometry(QRect(140, 260, 81, 31));

        retranslateUi(Serial);

        QMetaObject::connectSlotsByName(Serial);
    } // setupUi

    void retranslateUi(QDialog *Serial)
    {
        Serial->setWindowTitle(QApplication::translate("Serial", "Dialog", 0));
        groupBox->setTitle(QApplication::translate("Serial", "\344\270\262\345\217\243\345\217\202\346\225\260", 0));
        label_5->setText(QApplication::translate("Serial", "\345\201\234\346\255\242\344\275\215\357\274\232", 0));
        label_4->setText(QApplication::translate("Serial", "\346\225\260\346\215\256\344\275\215\357\274\232", 0));
        label_2->setText(QApplication::translate("Serial", "\347\253\257  \345\217\243\357\274\232", 0));
        label_3->setText(QApplication::translate("Serial", "\346\263\242\347\211\271\347\216\207\357\274\232", 0));
        label_6->setText(QApplication::translate("Serial", "\346\240\241  \351\252\214\357\274\232", 0));
        comboBox_Com->clear();
        comboBox_Com->insertItems(0, QStringList()
         << QString()
        );
        comboBox_Parity->clear();
        comboBox_Parity->insertItems(0, QStringList()
         << QApplication::translate("Serial", "None", 0)
         << QApplication::translate("Serial", "Odd", 0)
         << QApplication::translate("Serial", "Even", 0)
        );
        comboBox_DataBits->clear();
        comboBox_DataBits->insertItems(0, QStringList()
         << QApplication::translate("Serial", "8", 0)
         << QApplication::translate("Serial", "7", 0)
         << QApplication::translate("Serial", "6", 0)
         << QApplication::translate("Serial", "5", 0)
        );
        comboBox_StopBits->clear();
        comboBox_StopBits->insertItems(0, QStringList()
         << QApplication::translate("Serial", "1", 0)
         << QApplication::translate("Serial", "2", 0)
        );
        pushButton_Switch->setText(QApplication::translate("Serial", "\346\211\223\345\274\200\344\270\262\345\217\243", 0));
    } // retranslateUi

};

namespace Ui {
    class Serial: public Ui_Serial {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERIAL_H
