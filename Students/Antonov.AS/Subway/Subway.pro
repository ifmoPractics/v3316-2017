#-------------------------------------------------
#
# Project created by QtCreator 2017-10-16T20:06:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Subway
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        subwaymap.cpp \
    station.cpp \
    distance.cpp \
    branch.cpp \
    createnewbranchdialog.cpp \
    createnewstationdialog.cpp \
    makeringorlinedialog.cpp \
    junction.cpp \
    createjunctiondialog.cpp

HEADERS += \
        subwaymap.h \
    station.h \
    distance.h \
    branch.h \
    createnewbranchdialog.h \
    createnewstationdialog.h \
    makeringorlinedialog.h \
    junction.h \
    createjunctiondialog.h

FORMS += \
        subwaymap.ui \
    createnewbranchdialog.ui \
    createnewstationdialog.ui \
    makeringorlinedialog.ui \
    createjunctiondialog.ui


DISTFILES +=

RESOURCES += \
    res.qrc


