TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
 bin/open62541.c

HEADERS += \
     bin/open62541.h

unix:!macx: LIBS += -L$$PWD/bin/ -lopen62541

INCLUDEPATH += $$PWD/bin
DEPENDPATH += $$PWD/bin

unix:!macx: PRE_TARGETDEPS += $$PWD/bin/libopen62541.a
