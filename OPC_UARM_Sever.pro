QT += core
QT -= gui

TARGET = OPC_UARM_Sever
CONFIG += console
CONFIG -= app_bundle
CONFIG += c++11
INCLUDEPATH += /home/mark/Schreibtisch/Studium/IoT/mosquitto-1.5

TEMPLATE = app

SOURCES += main.cpp \
    open62541.c


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/./release/ -lopen62541
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/./debug/ -lopen62541
else:unix: LIBS += -L$$PWD/./ -lopen62541

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/./release/libopen62541.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/./debug/libopen62541.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/./release/open62541.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/./debug/open62541.lib
else:unix: PRE_TARGETDEPS += $$PWD/./libopen62541.a

HEADERS += \
    open62541.h


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../usr/local/lib/release/ -lpaho-mqttpp3
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../usr/local/lib/debug/ -lpaho-mqttpp3
else:unix: LIBS += -L$$PWD/../../../../usr/local/lib/ -lpaho-mqttpp3

INCLUDEPATH += $$PWD/../../../../usr/local/include/mqtt
DEPENDPATH += $$PWD/../../../../usr/local/include/mqtt
