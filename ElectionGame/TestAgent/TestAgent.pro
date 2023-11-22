include( ../common.pri )

QT       += core testlib
QT       -= gui

TARGET = tst_testagent
CONFIG   += testcase
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += \
    ../Course/deck.cpp \
    ../Course/formatexception.cpp \
    ../Course/game.cpp \
    ../Course/gameexception.cpp \
    ../Course/ioexception.cpp \
    ../Course/keyexception.cpp \
    ../Course/location.cpp \
    ../Course/player.cpp \
    ../Course/random.cpp \
    ../Course/settingsreader.cpp \
    ../Course/stateexception.cpp \
    ../Student/agent.cpp \
    tst_testagent.cpp

HEADERS  += \
    ../Course/deck.h \
    ../Course/game.h \
    ../Course/location.h \
    ../Course/player.h \
    ../Student/agent.h \

DEFINES += SRCDIR=\\\"$$PWD/\\\"

INCLUDEPATH += $$PWD/../Course $$PWD/../Student
DEPENDPATH += $$PWD/../Course $$PWD/../Student
