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
    managewdg.cpp \
    receivnavdata.cpp \
    navdata.c \
    perform_nav_data.cpp

HEADERS  += mainwindow.h \
    commandegen.h \
    udp_sender.h \
    debug.h \
    com.h \
    managewdg.h \
    navdata.h \
    receivnavdata.h \
    navdata_structs.h \
    perform_nav_data.h

FORMS    += mainwindow.ui
