#-------------------------------------------------
#
# Project created by QtCreator 2016-12-07T19:58:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = wyglad
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    App.cpp \
    DataImage.cpp \
    NoCompressed.cpp \
    Own5Bits.cpp \
    RLE.cpp \
    decompress.cpp

HEADERS  += mainwindow.h \
    RLE.h \
    Algorithm.h \
    App.h \
    DataImage.h \
    Enum.h \
    NoCompressed.h \
    Own5Bits.h \
    decompress.h

FORMS    += mainwindow.ui \
    decompress.ui
