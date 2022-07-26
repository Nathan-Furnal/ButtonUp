TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

include(../../config.pri)

HEADERS += \
    controller.h \
    view.h
SOURCES += \
    controller.cpp \
    main.cpp \
    view.cpp
