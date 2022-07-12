QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include(../../config.pri)

# You can your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000 # disables all the APIs deprecated before Qt 6.0.0

SOURCES +=
HEADERS +=

# Default rules for deployment.
LIBRARY_OUT_PWD = $$clean_path($$OUT_PWD/$$relative_path($$PWD, $$_PRO_FILE_PWD_))
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = $${LIBRARY_OUT_PWD}/opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

