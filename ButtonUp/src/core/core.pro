CONFIG -= qt
CONFIG += c++17

TEMPLATE = lib

include(../../config.pri)

CONFIG += $${LIB_MODE}

HEADERS += \
    button.h \
    buttonstack.h \
    game.h

SOURCES += \
    buttonstack.cpp \
    game.cpp

DISTFILES += \
    core.pri
