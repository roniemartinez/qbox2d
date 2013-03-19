#-------------------------------------------------
#
# Project created by QtCreator 2013-03-19T00:34:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Tiles
TEMPLATE = app

include(../../box2d.pri)
include(../../qbox2d.pri)

SOURCES += main.cpp\
        mainwindow.cpp \
    ../qbox2dview.cpp

HEADERS  += mainwindow.h \
    ../qbox2dview.h
