# -------------------------------------------------
# Project created by QtCreator 2010-05-19T15:28:06
# -------------------------------------------------
QT += network
TARGET = confero
TEMPLATE = app
DESTDIR = bin
OBJECTS_DIR = bin/obj
MOC_DIR = .qtSol
UI_DIR = .qtSol
SOURCES += \
    src/Random.cpp \
    src/main.cpp \
    src/confero.cpp \
    src/document/SciWrapper.cpp \
    src/document/Edit.cpp \
    src/document/DocumentManager.cpp \
    src/document/Document.cpp \
    src/document/DocHolder.cpp \
    src/document/Chat.cpp \
    src/net/SessionManager.cpp \
    src/net/Session.cpp \
    src/net/Packet.cpp \
    src/net/NetServer.cpp \
    src/net/NetManager.cpp \
    src/net/NetClientWriter.cpp \
    src/net/NetClient.cpp \
    src/net/HostID.cpp \
    src/net/ConferoNet.cpp
HEADERS += \
    src/Random.h \
    src/confero.h \
    src/document/SciWrapper.h \
    src/document/Edit.h \
    src/document/DocumentManager.h \
    src/document/Document.h \
    src/document/DocHolder.h \
    src/document/Chat.h \
    src/net/SessionManager.h \
    src/net/Session.h \
    src/net/PacketDefs.h \
    src/net/Packet.h \
    src/net/NetServer.h \
    src/net/NetManager.h \
    src/net/NetClientWriter.h \
    src/net/NetClient.h \
    src/net/HostID.h \
    src/net/ConferoNet.h
FORMS += \
    src/ui/ip.ui \
    src/ui/confero.ui
OTHER_FILES +=
LIBS += -l \
    qscintilla2

RESOURCES +=
