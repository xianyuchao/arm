#-------------------------------------------------
#
# Project created by QtCreator 2015-07-20T16:26:17
#
#-------------------------------------------------

QT       -= gui

TARGET = untitled
TEMPLATE = lib

DEFINES += UNTITLED_LIBRARY

SOURCES += testlib.cpp

HEADERS += testlib.h\
        untitled_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
