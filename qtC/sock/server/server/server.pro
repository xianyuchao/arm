#-------------------------------------------------
#
# Project created by QtCreator 2015-01-04T19:35:31
#
#-------------------------------------------------

QT       += core
QT       += network

QT       -= gui

TARGET = server
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    chat_server.cpp \
    my_socket.cpp

HEADERS += \
    chat_server.h \
    my_socket.h
