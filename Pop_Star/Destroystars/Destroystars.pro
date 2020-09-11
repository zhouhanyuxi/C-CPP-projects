#-------------------------------------------------
#
# Project created by QtCreator 2017-09-14T14:37:32
#
#-------------------------------------------------

QT       += core gui
QT       += sql
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Destroystars
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
        mainwindow.cpp \
    game.cpp \
    enddialog.cpp \
    star.cpp \
    recorddialog.cpp

HEADERS  += mainwindow.h \
    connection.h \
    game.h \
    enddialog.h \
    star.h \
    recorddialog.h

FORMS    += mainwindow.ui \
    game.ui \
    enddialog.ui \
    recorddialog.ui

RESOURCES += \
    mystyle.qrc \
    txt.qrc \
    images.qrc

RC_ICONS = tubiao.ico

DISTFILES +=


