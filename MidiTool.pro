#-------------------------------------------------
#
# Project created by QtCreator 2018-01-23T14:34:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MidiTool
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        MainWindow.cpp \
    Util.cpp \
    TrayIcon.cpp

HEADERS  += MainWindow.h \
    Util.h \
    TrayIcon.h

FORMS    += MainWindow.ui

include(systemaudio/systemaudio.pri)
include(qmidi/qmidi.pri)

LIBS += -lOle32 -lUser32 -lwinmm #-lpropsys

RESOURCES += \
    resources.qrc

QMAKE_LFLAGS_RELEASE += -static -static-libgcc
