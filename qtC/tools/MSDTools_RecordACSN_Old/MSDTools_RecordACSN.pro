#-------------------------------------------------
#
# Project created by QtCreator 2014-08-29T14:34:57
#
#-------------------------------------------------

QT       += core gui network multimedia serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MSDTools_RecordACSN
TEMPLATE = app

SOURCES += main.cpp\
        widget.cpp \
    hatcp.cpp \
    wirelesscontrol.cpp \
    serial.cpp \
    file.cpp

HEADERS  += widget.h \
    globalDefine.h \
    hatcp.h \
    wirelesscontrol.h \
    serial.h \
    file.h \
    getsn.h

FORMS    += widget.ui \
    serial.ui

RESOURCES += \
    src.qrc

unix|win32: LIBS += -L$$PWD/Lib/ -lwlanapi

INCLUDEPATH += $$PWD/Lib
DEPENDPATH += $$PWD/Lib

unix|win32: LIBS += -L$$PWD/Lib/ -liphlpapi

INCLUDEPATH += $$PWD/Lib
DEPENDPATH += $$PWD/Lib

unix|win32: LIBS += -L$$PWD/lib/ -llibeay32

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

OTHER_FILES += \
    Lib/x64/iphlpapi.lib \
    Lib/x64/wlanapi.lib

unix|win32: LIBS += -L$$PWD/ -lgetSN

INCLUDEPATH += $$PWD/
DEPENDPATH += $$PWD/

unix|win32-g++: PRE_TARGETDEPS += $$PWD/libgetSN.a

unix|win32: LIBS += -L$$PWD/lib/ -lMDll
