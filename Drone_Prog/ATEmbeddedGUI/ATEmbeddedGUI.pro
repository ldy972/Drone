#-------------------------------------------------
#
# Project created by QtCreator 2015-11-20T11:17:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ATEmbeddedGUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    commandegen.cpp \
    udp_sender.c \
    com.c \
    managewdg.cpp

HEADERS  += mainwindow.h \
    commandegen.h \
    udp_sender.h \
    debug.h \
    com.h \
    managewdg.h

FORMS    += mainwindow.ui
