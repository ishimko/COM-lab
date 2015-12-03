#-------------------------------------------------
#
# Project created by QtCreator 2015-12-03T16:00:49
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = COM-lab
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    portselecterwindow.cpp

HEADERS  += mainwindow.h \
    portselecterwindow.h \
    types.h

FORMS    += mainwindow.ui \
    portselecterwindow.ui

RESOURCES +=
