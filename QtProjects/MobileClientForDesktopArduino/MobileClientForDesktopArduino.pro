#-------------------------------------------------
#
# Project created by QtCreator 2016-06-07T12:50:17
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MobileClientForDesktopArduino
TEMPLATE = app


SOURCES += main.cpp\
        Widget.cpp

HEADERS  += Widget.h

FORMS    += Widget.ui

CONFIG += mobility
MOBILITY = 

QMAKE_CXXFLAGS += -std=gnu++14
