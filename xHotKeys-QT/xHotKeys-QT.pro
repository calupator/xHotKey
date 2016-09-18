#-------------------------------------------------
#
# Project created by QtCreator 2016-09-18T21:15:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = xHotKeys-QT
TEMPLATE = app


SOURCES += main.cpp\
        xHKwindow.cpp

HEADERS  += xHKwindow.h

FORMS    += xHKwindow.ui

win32: LIBS += -L$$PWD/../Debug/x64/ -lxHotKeysCore

INCLUDEPATH += $$PWD/../xHotKeysCore
DEPENDPATH += $$PWD/../xHotKeysCore
