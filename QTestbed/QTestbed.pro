#-------------------------------------------------
#
# Project created by QtCreator 2013-03-19T22:07:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QTestbed
TEMPLATE = app

include(../qbox2d.pri)

SOURCES += main.cpp\
        mainwindow.cpp \
    qbox2dview.cpp \
    tests/varyingfriction.cpp \
    tests/tiles.cpp \
    tests/varyingrestitution.cpp

HEADERS  += mainwindow.h \
    qbox2dview.h \
    tests/varyingfriction.h \
    tests/tiles.h \
    tests/varyingrestitution.h

FORMS    += mainwindow.ui
