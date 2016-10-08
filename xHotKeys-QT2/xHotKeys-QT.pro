#-------------------------------------------------
#
# Project created by QtCreator 2016-09-18T21:15:53
#
#-------------------------------------------------

#QT       += core gui

#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT += widgets

TARGET = xHotKeys-QT
TEMPLATE = app
DESTDIR = ../Debug/x64

SOURCES += main.cpp\
        xHKwindow.cpp

HEADERS  += xHKwindow.h

FORMS    += xHKwindow.ui

win32: LIBS += -L$$PWD/../Debug/x64/ -lxHotKeysCore

INCLUDEPATH += $$PWD/../xHotKeysCore
DEPENDPATH += $$PWD/../xHotKeysCore


win32-msvc*{
    LIBS += -luser32
}
