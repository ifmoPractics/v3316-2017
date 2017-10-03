#-------------------------------------------------
#
# Project created by QtCreator 2017-09-28T21:35:33
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Tetris_design
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS


SOURCES += \
        main.cpp \
        tetriswindow.cpp \
        tetriscontroller.cpp \
    tetrismodel.cpp \
    soundcontroller.cpp

HEADERS += \
        tetriswindow.h \
        tetriscontroller.h \
    tetrismodel.h \
    soundcontroller.h \
    savecontroller.h

RESOURCES += \
    resources\res.qrc

DISTFILES += \
    style.css
