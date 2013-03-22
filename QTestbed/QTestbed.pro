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
    tests/varyingrestitution.cpp \
    tests/gears.cpp \
    tests/charactercollision.cpp \
    tests/cantilever.cpp \
    tests/theojansen.cpp \
    tests/bullettest.cpp \
    tests/tumbler.cpp \
    tests/car.cpp \
    qbox2dtest.cpp \
    tests/verticalstack.cpp \
    tests/web.cpp \
    tests/shapeediting.cpp

HEADERS  += mainwindow.h \
    qbox2dview.h \
    tests/varyingfriction.h \
    tests/tiles.h \
    tests/varyingrestitution.h \
    tests/gears.h \
    tests/charactercollision.h \
    tests/cantilever.h \
    tests/theojansen.h \
    tests/bullettest.h \
    tests/tumbler.h \
    tests/car.h \
    qbox2dtest.h \
    tests/verticalstack.h \
    tests/web.h \
    tests/shapeediting.h

FORMS    += mainwindow.ui
