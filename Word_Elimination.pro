#-------------------------------------------------
#
# Project created by QtCreator 2023-04-27T08:37:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Word_Elimination
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


SOURCES += \
        main.cpp \
        widget.cpp \
    answerwindow.cpp \
    savemanager.cpp \
    makerwindow.cpp \
    player.cpp \
    answer.cpp \
    maker.cpp \
    startgame.cpp

HEADERS += \
        widget.h \
    answerwindow.h \
    savemanager.h \
    makerwindow.h \
    player.h \
    answer.h \
    maker.h \
    startgame.h

FORMS += \
        widget.ui \
    answerwindow.ui \
    makerwindow.ui \
    startgame.ui
