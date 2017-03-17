#-------------------------------------------------
#
# Project created by QtCreator 2017-03-15T01:36:27
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Eaton
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    ResultsWindow.cpp \
    Search.cpp \
    Error.cpp

HEADERS  += MainWindow.hpp \
    json.hpp \
    ResultsWindow.hpp \
    main.hpp \
    Search.hpp \
    Error.hpp

FORMS    += MainWindow.ui \
    ResultsWindow.ui


# Use C++14 and link curl library
CONFIG += c++14
QMAKE_LFLAGS += -lcurl
