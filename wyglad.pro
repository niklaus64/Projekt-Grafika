#-------------------------------------------------
#
# Project created by QtCreator 2016-12-07T19:58:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = wyglad
TEMPLATE = app
CONFIG += c++14
QMAKE_CXXFLAGS += -std=c++1y


SOURCES += main.cpp\
        mainwindow.cpp \
    DataImage.cpp \
    Own5Bits.cpp \
    RLE.cpp \
    decompress.cpp \
    ByteRun.cpp \
    Error.cpp \

HEADERS  += mainwindow.h \
    RLE.h \
    Algorithm.h \
    DataImage.h \
    Enum.h \
    Own5Bits.h \
    decompress.h \
    ByteRun.h \
    Error.h \
    HeaderBMP.h

FORMS    += mainwindow.ui \
    decompress.ui
