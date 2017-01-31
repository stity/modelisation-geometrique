#-------------------------------------------------
#
# Project created by QtCreator 2017-01-10T17:03:00
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BE1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    sommet.cpp \
    triangle.cpp \
    loader.cpp \
    maillage.cpp \
    gasket.cpp \
    gldisplay.cpp

HEADERS  += mainwindow.h \
    sommet.h \
    triangle.h \
    loader.h \
    maillage.h \
    gasket.h \
    gldisplay.h

FORMS    += mainwindow.ui
