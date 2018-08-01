QT += qml quick

TARGET = OPC_UARM_Sever
CONFIG += console

CONFIG += c++11

TEMPLATE = app

SOURCES += main.cpp \
    bin/open62541.c \
    Mqtt/mqtt.cpp \
    OPCUA/opcua.cpp \
    controller.cpp

LIBS += -lmosquittopp -lmosquitto

HEADERS += \
     bin/open62541.h \
    Mqtt/mqtt.h \
    OPCUA/opcua.h \
    controller.h

unix:!macx: LIBS += -L$$PWD/bin/ -lopen62541

INCLUDEPATH += $$PWD/bin
DEPENDPATH += $$PWD/bin

unix:!macx: PRE_TARGETDEPS += $$PWD/bin/libopen62541.a
