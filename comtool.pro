#-------------------------------------------------
#
# Project created by QtCreator 2019-12-30T10:11:49
#
#-------------------------------------------------

QT       += core gui
QT       += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = comtool
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++0x


SOURCES += main.cpp\
        comtoolwindow.cpp \
    myserial.cpp \
    clickcombobox.cpp

HEADERS  += comtoolwindow.h \
    myserial.h \
    clickcombobox.h

FORMS    += comtoolwindow.ui
