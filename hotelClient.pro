#-------------------------------------------------
#
# Project created by QtCreator 2016-06-16T12:00:53
#
#-------------------------------------------------

QT       += core gui
QT       += network widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = hotelClient
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    roominfodialog.cpp \
    guestinfodialog.cpp \
    newguestdialog.cpp \
    savefileclass.cpp

HEADERS  += mainwindow.h \
    roominfodialog.h \
    guestinfodialog.h \
    newguestdialog.h \
    savefileclass.h

FORMS    += mainwindow.ui \
    roominfodialog.ui \
    guestinfodialog.ui \
    newguestdialog.ui
