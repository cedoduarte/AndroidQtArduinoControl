#-------------------------------------------------
#
# Project created by QtCreator 2016-03-30T11:59:53
#
#-------------------------------------------------

QT       += core gui serialport network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DesktopServerSerialPortArduino
TEMPLATE = app


SOURCES += main.cpp\
        Widget.cpp \
    DuArduino.cpp \
    DuTcpServerForAndroid.cpp

HEADERS  += Widget.h \
    DuArduino.h \
    DuTcpServerForAndroid.h

FORMS    += Widget.ui

QMAKE_CXXFLAGS += -std=gnu++14
