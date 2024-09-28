QT += core network
QT -= gui

CONFIG += c++11

TARGET = ServerCloud
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    server.cpp \
    client.cpp \
    settingsfile.cpp \
    authorization.cpp \
    file.cpp \
    folder.cpp \
    synchronization.cpp \
    replace.cpp

HEADERS += \
    server.h \
    client.h \
    settingsfile.h \
    authorization.h \
    file.h \
    folder.h \
    synchronization.h \
    replace.h
