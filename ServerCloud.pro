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
    state.cpp \
    settingsfile.cpp \
    controllersql.cpp \
    filemanager.cpp \
    connect.cpp \
    protocol.cpp \
    tcpip.cpp \
    udp.cpp \
    encryption.cpp \
    output.cpp \
    sendinformation.cpp \
    senddata.cpp \
    information.cpp \
    json.cpp \
    authorization.cpp \
    copy.cpp \
    delete.cpp \
    file.cpp \
    folder.cpp

HEADERS += \
    server.h \
    client.h \
    state.h \
    settingsfile.h \
    controllersql.h \
    filemanager.h \
    connect.h \
    protocol.h \
    tcpip.h \
    udp.h \
    encryption.h \
    output.h \
    sendinformation.h \
    senddata.h \
    information.h \
    json.h \
    authorization.h \
    copy.h \
    delete.h \
    file.h \
    folder.h
