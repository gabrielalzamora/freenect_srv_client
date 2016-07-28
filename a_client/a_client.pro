#-------------------------------------------------
#
# Project created by QtCreator 2016-07-08T10:38:25
#
#-------------------------------------------------

QT       += core gui network opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = a_client
TEMPLATE = app


SOURCES += main.cpp\
           mainwindow.cpp\
           data.cpp

HEADERS  += mainwindow.h\
            data.h

FORMS    += mainwindow.ui

# due to problems compiling std::vector std::mutex and so on?????
QMAKE_CXXFLAGS  += -std=gnu++11
