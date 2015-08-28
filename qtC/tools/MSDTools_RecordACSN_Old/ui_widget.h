/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QLabel *logoLabel;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *SNLabel;
    QLineEdit *SNEdit;
    QPushButton *SNSelectButton;
    QHBoxLayout *horizontalLayout_3;
    QLabel *SSIDLabel;
    QLineEdit *SSIDEdit;
    QSpacerItem *horizontalSpacer;
    QWidget *horizontalLayoutWidget_4;
    QHBoxLayout *horizontalLayout_4;
    QLabel *stateLabel;
    QLabel *ledLabel;
    QLabel *theStateLabel;
    QSpacerItem *horizontalSpacer_2;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *aboutButton;
    QPushButton *aboutButtonSerial;
    QPushButton *writeButton;
    QCheckBox *reWriteCheckBox;
    QCheckBox *gunCheckBox;
    QLabel *BackgroundLabel;
    QListWidget *listWidget;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *label;
    QLabel *label_2;
    QListWidget *SNList;
    QLabel *label_3;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(891, 360);
        Widget->setAcceptDrops(false);
        QIcon icon;
        icon.addFile(QStringLiteral(":/img/img/icon.ico"), QSize(), QIcon::Normal, QIcon::Off);
        Widget->setWindowIcon(icon);
        logoLabel = new QLabel(Widget);
        logoLabel->setObjectName(QStringLiteral("logoLabel"));
        logoLabel->setGeometry(QRect(0, 0, 518, 124));
        logoLabel->setPixmap(QPixmap(QString::fromUtf8(":/img/img/logo.png")));
        verticalLayoutWidget = new QWidget(Widget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 130, 501, 81));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        SNLabel = new QLabel(verticalLayoutWidget);
        SNLabel->setObjectName(QStringLiteral("SNLabel"));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(14);
        SNLabel->setFont(font);

        horizontalLayout_2->addWidget(SNLabel);

        SNEdit = new QLineEdit(verticalLayoutWidget);
        SNEdit->setObjectName(QStringLiteral("SNEdit"));
        SNEdit->setFont(font);

        horizontalLayout_2->addWidget(SNEdit);

        SNSelectButton = new QPushButton(verticalLayoutWidget);
        SNSelectButton->setObjectName(QStringLiteral("SNSelectButton"));
        SNSelectButton->setFont(font);

        horizontalLayout_2->addWidget(SNSelectButton);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        SSIDLabel = new QLabel(verticalLayoutWidget);
        SSIDLabel->setObjectName(QStringLiteral("SSIDLabel"));
        SSIDLabel->setFont(font);

        horizontalLayout_3->addWidget(SSIDLabel);

        SSIDEdit = new QLineEdit(verticalLayoutWidget);
        SSIDEdit->setObjectName(QStringLiteral("SSIDEdit"));
        SSIDEdit->setFont(font);
        SSIDEdit->setReadOnly(true);

        horizontalLayout_3->addWidget(SSIDEdit);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayoutWidget_4 = new QWidget(Widget);
        horizontalLayoutWidget_4->setObjectName(QStringLiteral("horizontalLayoutWidget_4"));
        horizontalLayoutWidget_4->setGeometry(QRect(10, 240, 241, 33));
        horizontalLayout_4 = new QHBoxLayout(horizontalLayoutWidget_4);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        stateLabel = new QLabel(horizontalLayoutWidget_4);
        stateLabel->setObjectName(QStringLiteral("stateLabel"));
        stateLabel->setFont(font);

        horizontalLayout_4->addWidget(stateLabel);

        ledLabel = new QLabel(horizontalLayoutWidget_4);
        ledLabel->setObjectName(QStringLiteral("ledLabel"));
        ledLabel->setPixmap(QPixmap(QString::fromUtf8(":/img/img/red.png")));

        horizontalLayout_4->addWidget(ledLabel);

        theStateLabel = new QLabel(horizontalLayoutWidget_4);
        theStateLabel->setObjectName(QStringLiteral("theStateLabel"));
        theStateLabel->setFont(font);

        horizontalLayout_4->addWidget(theStateLabel);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);

        horizontalLayoutWidget = new QWidget(Widget);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(260, 240, 250, 37));
        horizontalLayout_5 = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        aboutButton = new QPushButton(horizontalLayoutWidget);
        aboutButton->setObjectName(QStringLiteral("aboutButton"));
        aboutButton->setFont(font);

        horizontalLayout_5->addWidget(aboutButton);

        aboutButtonSerial = new QPushButton(horizontalLayoutWidget);
        aboutButtonSerial->setObjectName(QStringLiteral("aboutButtonSerial"));
        aboutButtonSerial->setFont(font);

        horizontalLayout_5->addWidget(aboutButtonSerial);

        writeButton = new QPushButton(horizontalLayoutWidget);
        writeButton->setObjectName(QStringLiteral("writeButton"));
        writeButton->setFont(font);

        horizontalLayout_5->addWidget(writeButton);

        reWriteCheckBox = new QCheckBox(Widget);
        reWriteCheckBox->setObjectName(QStringLiteral("reWriteCheckBox"));
        reWriteCheckBox->setEnabled(false);
        reWriteCheckBox->setGeometry(QRect(450, 220, 59, 16));
        gunCheckBox = new QCheckBox(Widget);
        gunCheckBox->setObjectName(QStringLiteral("gunCheckBox"));
        gunCheckBox->setGeometry(QRect(340, 220, 107, 16));
        BackgroundLabel = new QLabel(Widget);
        BackgroundLabel->setObjectName(QStringLiteral("BackgroundLabel"));
        BackgroundLabel->setGeometry(QRect(0, 0, 521, 281));
        BackgroundLabel->setPixmap(QPixmap(QString::fromUtf8(":/img/img/redB.png")));
        listWidget = new QListWidget(Widget);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(530, 30, 141, 221));
        pushButton = new QPushButton(Widget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(530, 290, 75, 23));
        pushButton_2 = new QPushButton(Widget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(530, 320, 75, 23));
        label = new QLabel(Widget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(530, 260, 171, 21));
        label_2 = new QLabel(Widget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(530, 10, 171, 21));
        SNList = new QListWidget(Widget);
        SNList->setObjectName(QStringLiteral("SNList"));
        SNList->setGeometry(QRect(690, 30, 181, 301));
        label_3 = new QLabel(Widget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(690, 10, 171, 21));
        BackgroundLabel->raise();
        logoLabel->raise();
        verticalLayoutWidget->raise();
        horizontalLayoutWidget_4->raise();
        horizontalLayoutWidget->raise();
        reWriteCheckBox->raise();
        gunCheckBox->raise();
        listWidget->raise();
        pushButton->raise();
        pushButton_2->raise();
        label->raise();
        label_2->raise();
        SNList->raise();
        label_3->raise();

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "\344\272\247\347\272\277WIFI\346\243\200\346\265\213\345\267\245\345\205\267(\345\256\266\347\224\250\347\251\272\350\260\203)", 0));
        logoLabel->setText(QString());
        SNLabel->setText(QApplication::translate("Widget", "\347\203\247\345\275\225SN\347\240\201\357\274\232", 0));
        SNEdit->setText(QString());
        SNSelectButton->setText(QApplication::translate("Widget", "\345\205\250\351\200\211", 0));
        SSIDLabel->setText(QApplication::translate("Widget", "\350\277\236\346\216\245SSID\357\274\232", 0));
        stateLabel->setText(QApplication::translate("Widget", "\347\212\266\346\200\201\357\274\232", 0));
        ledLabel->setText(QString());
        theStateLabel->setText(QApplication::translate("Widget", "\345\201\234\346\255\242", 0));
        aboutButton->setText(QApplication::translate("Widget", "\345\205\263\344\272\216", 0));
        aboutButtonSerial->setText(QApplication::translate("Widget", "\344\270\262\345\217\243", 0));
        writeButton->setText(QApplication::translate("Widget", "\345\274\200\345\247\213\346\243\200\346\265\213", 0));
        reWriteCheckBox->setText(QApplication::translate("Widget", "\351\207\215\345\206\231SN", 0));
        gunCheckBox->setText(QApplication::translate("Widget", "\342\200\234\345\233\236\350\275\246\342\200\235\346\211\253\347\240\201\346\236\252", 0));
        BackgroundLabel->setText(QString());
        pushButton->setText(QApplication::translate("Widget", "\345\210\267\346\226\260", 0));
        pushButton_2->setText(QApplication::translate("Widget", "\350\277\236\346\216\245", 0));
        label->setText(QApplication::translate("Widget", "\345\275\223\345\211\215\347\275\221\347\273\234\357\274\232", 0));
        label_2->setText(QApplication::translate("Widget", "\345\217\257\347\224\250\347\275\221\347\273\234\357\274\232", 0));
        label_3->setText(QApplication::translate("Widget", "\345\276\205\346\243\200SN\357\274\232", 0));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
