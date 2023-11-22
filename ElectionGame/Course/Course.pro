include( ../common.pri )

QT       += core

TARGET = Course
CONFIG += staticlib

SOURCES += \
    councilor.cpp \
    deck.cpp \
    formatexception.cpp \
    game.cpp \
    gameexception.cpp \
    influence.cpp \
    ioexception.cpp \
    keyexception.cpp \
    location.cpp \
    player.cpp \
    random.cpp \
    rangeexception.cpp \
    settingsreader.cpp \
    stateexception.cpp \
    runner.cpp \
    controlexception.cpp \
    manualcontrol.cpp \
    withdrawaction.cpp

HEADERS += \
    agentinterface.h \
    cardinterface.h \
    councilor.h \
    deck.h \
    deckinterface.h \
    formatexception.h \
    game.h \
    gameexception.h \
    influence.h \
    ioexception.h \
    keyexception.h \
    location.h \
    player.h \
    random.h \
    rangeexception.h \
    settingsreader.h \
    stateexception.h \
    actioninterface.h \
    controlinterface.h \
    runner.h \
    controlexception.h \
    manualcontrol.h \
    withdrawaction.h \
    doxygeninfo.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
