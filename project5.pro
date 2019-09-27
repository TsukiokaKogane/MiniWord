#-------------------------------------------------
#
# Project created by QtCreator 2018-05-31T22:05:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = project5
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

SOURCES += rowlist.cpp \
    filesavedialog.cpp \
    finddialog.cpp \
    replacedialog.cpp \
    myqlabel.cpp
HEADERS += rowlist.h \
    filesavedialog.h \
    finddialog.h \
    replacedialog.h \
    myqlabel.h
HEADERS += mainwindow.h
SOURCES += mainwindow.cpp
HEADERS += main.h
SOURCES += main.cpp


FORMS +=  mainwindow.ui \
    filesavedialog.ui \
    finddialog.ui \
    replacedialog.ui
