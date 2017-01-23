#-------------------------------------------------
#
# Project created by QtCreator 2017-01-10T17:03:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BE1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    sommet.cpp \
    triangle.cpp \
    loader.cpp \
    maillage.cpp

HEADERS  += mainwindow.h \
    sommet.h \
    triangle.h \
    loader.h \
    maillage.h

FORMS    += mainwindow.ui
