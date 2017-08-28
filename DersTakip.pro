#-------------------------------------------------
#
# Project created by QtCreator 2017-08-06T11:43:47
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DersTakip
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    database.cpp \
    htmlyaz.cpp

HEADERS  += mainwindow.h \
    database.h \
    htmlyaz.h

FORMS    += mainwindow.ui

RESOURCES += \
    img.qrc
