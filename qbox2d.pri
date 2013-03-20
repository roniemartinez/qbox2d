# Box2D sources

include(box2d.pri)

INCLUDEPATH += $$PWD
SOURCES += \
    $$PWD/qbox2dworld.cpp \
	$$PWD/qbox2dbody.cpp 

HEADERS += \
    $$PWD/qbox2dworld.h \
	$$PWD/qbox2dcommon.h \
	$$PWD/qbox2dbody.h 
