TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

include(../../config.pri)

HEADERS += \
    controller.h \
    util.h \
    view.h
SOURCES += \
    controller.cpp \
    main.cpp \
    view.cpp
