#-------------------------------------------------
#
# Project created by QtCreator 2013-03-10T13:37:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QBox2D
TEMPLATE = app

include(../box2d.pri)

SOURCES += main.cpp\
    ../qbox2dworld.cpp \
    ../qbox2dbody.cpp

HEADERS  += \
    ../qbox2dworld.h \
    ../qbox2dcommon.h \
    ../qbox2dbody.h

OTHER_FILES += \
    ../README.md
