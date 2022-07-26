TEMPLATE = app
CONFIG -= qt
CONFIG -= app_bundle
CONFIG += console

include(../../config.pri)

INCLUDEPATH += ../../libs/

SOURCES += \
    main.cpp \
    test_buttonStack.cpp \
    test_game.cpp
