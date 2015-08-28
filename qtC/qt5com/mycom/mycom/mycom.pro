#-------------------------------------------------
#
# Project created by QtCreator 2015-07-19T14:25:36
#
#-------------------------------------------------

QT       += core gui

QT       += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mycom
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
    ../../../mylib/untitled/testlib.h

FORMS    += mainwindow.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../mylib/build-untitled-Desktop_Qt_5_4_0_MinGW_32bit-Debug/release/ -luntitled
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../mylib/build-untitled-Desktop_Qt_5_4_0_MinGW_32bit-Debug/debug/ -luntitled
else:unix: LIBS += -L$$PWD/../../../mylib/build-untitled-Desktop_Qt_5_4_0_MinGW_32bit-Debug/ -luntitled

INCLUDEPATH += $$PWD/../../../mylib/build-untitled-Desktop_Qt_5_4_0_MinGW_32bit-Debug/debug
DEPENDPATH += $$PWD/../../../mylib/build-untitled-Desktop_Qt_5_4_0_MinGW_32bit-Debug/debug
INCLUDEPATH += $$PWD/../../../mylib/untitled

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../mylib/build-untitled-Desktop_Qt_5_4_0_MinGW_32bit-Debug/release/ -luntitled
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../mylib/build-untitled-Desktop_Qt_5_4_0_MinGW_32bit-Debug/debug/ -luntitled
else:unix: LIBS += -L$$PWD/../../../mylib/build-untitled-Desktop_Qt_5_4_0_MinGW_32bit-Debug/ -luntitled

INCLUDEPATH += $$PWD/../../../mylib/build-untitled-Desktop_Qt_5_4_0_MinGW_32bit-Debug/debug
DEPENDPATH += $$PWD/../../../mylib/build-untitled-Desktop_Qt_5_4_0_MinGW_32bit-Debug/debug

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../mylib/untitled/release/ -luntitled
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../mylib/untitled/debug/ -luntitled
else:unix: LIBS += -L$$PWD/../../../mylib/untitled/ -luntitled

INCLUDEPATH += $$PWD/../../../mylib/untitled
DEPENDPATH += $$PWD/../../../mylib/untitled
