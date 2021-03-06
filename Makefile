#############################################################################
# Makefile for building: bin/confero
# Generated by qmake (2.01a) (Qt 4.7.2) on: Fri Jun 10 17:45:37 2011
# Project:  Confero.pro
# Template: app
# Command: /usr/bin/qmake-qt4 -spec /usr/share/qt4/mkspecs/linux-g++ CONFIG+=debug QMLJSDEBUGGER_PATH=/usr/share/qtcreator/qml/qmljsdebugger -o Makefile Confero.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_GUI_LIB -DQT_NETWORK_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -g -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -pipe -g -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++ -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtNetwork -I/usr/include/qt4/QtGui -I/usr/include/qt4 -I.qtSol -I.qtSol
LINK          = g++
LFLAGS        = 
LIBS          = $(SUBLIBS)  -L/usr/lib -l qscintilla2 -lQtGui -lQtNetwork -lQtCore -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/bin/qmake-qt4
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = bin/obj/

####### Files

SOURCES       = src/Random.cpp \
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
		src/net/ConferoNet.cpp .qtSol/moc_confero.cpp \
		.qtSol/moc_SciWrapper.cpp \
		.qtSol/moc_DocumentManager.cpp \
		.qtSol/moc_Chat.cpp \
		.qtSol/moc_NetServer.cpp \
		.qtSol/moc_NetManager.cpp \
		.qtSol/moc_NetClientWriter.cpp \
		.qtSol/moc_NetClient.cpp
OBJECTS       = bin/obj/Random.o \
		bin/obj/main.o \
		bin/obj/confero.o \
		bin/obj/SciWrapper.o \
		bin/obj/Edit.o \
		bin/obj/DocumentManager.o \
		bin/obj/Document.o \
		bin/obj/DocHolder.o \
		bin/obj/Chat.o \
		bin/obj/SessionManager.o \
		bin/obj/Session.o \
		bin/obj/Packet.o \
		bin/obj/NetServer.o \
		bin/obj/NetManager.o \
		bin/obj/NetClientWriter.o \
		bin/obj/NetClient.o \
		bin/obj/HostID.o \
		bin/obj/ConferoNet.o \
		bin/obj/moc_confero.o \
		bin/obj/moc_SciWrapper.o \
		bin/obj/moc_DocumentManager.o \
		bin/obj/moc_Chat.o \
		bin/obj/moc_NetServer.o \
		bin/obj/moc_NetManager.o \
		bin/obj/moc_NetClientWriter.o \
		bin/obj/moc_NetClient.o
DIST          = /usr/share/qt4/mkspecs/common/g++.conf \
		/usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/debug.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		Confero.pro
QMAKE_TARGET  = confero
DESTDIR       = bin/
TARGET        = bin/confero

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET): .qtSol/ui_ip.h .qtSol/ui_confero.h $(OBJECTS)  
	@$(CHK_DIR_EXISTS) bin/ || $(MKDIR) bin/ 
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: Confero.pro  /usr/share/qt4/mkspecs/linux-g++/qmake.conf /usr/share/qt4/mkspecs/common/g++.conf \
		/usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/debug.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/lib/libQtGui.prl \
		/usr/lib/libQtNetwork.prl \
		/usr/lib/libQtCore.prl
	$(QMAKE) -spec /usr/share/qt4/mkspecs/linux-g++ CONFIG+=debug QMLJSDEBUGGER_PATH=/usr/share/qtcreator/qml/qmljsdebugger -o Makefile Confero.pro
/usr/share/qt4/mkspecs/common/g++.conf:
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
/usr/share/qt4/mkspecs/features/debug.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
/usr/lib/libQtGui.prl:
/usr/lib/libQtNetwork.prl:
/usr/lib/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -spec /usr/share/qt4/mkspecs/linux-g++ CONFIG+=debug QMLJSDEBUGGER_PATH=/usr/share/qtcreator/qml/qmljsdebugger -o Makefile Confero.pro

dist: 
	@$(CHK_DIR_EXISTS) bin/obj/confero1.0.0 || $(MKDIR) bin/obj/confero1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) bin/obj/confero1.0.0/ && $(COPY_FILE) --parents src/Random.h src/confero.h src/document/SciWrapper.h src/document/Edit.h src/document/DocumentManager.h src/document/Document.h src/document/DocHolder.h src/document/Chat.h src/net/SessionManager.h src/net/Session.h src/net/PacketDefs.h src/net/Packet.h src/net/NetServer.h src/net/NetManager.h src/net/NetClientWriter.h src/net/NetClient.h src/net/HostID.h src/net/ConferoNet.h bin/obj/confero1.0.0/ && $(COPY_FILE) --parents src/Random.cpp src/main.cpp src/confero.cpp src/document/SciWrapper.cpp src/document/Edit.cpp src/document/DocumentManager.cpp src/document/Document.cpp src/document/DocHolder.cpp src/document/Chat.cpp src/net/SessionManager.cpp src/net/Session.cpp src/net/Packet.cpp src/net/NetServer.cpp src/net/NetManager.cpp src/net/NetClientWriter.cpp src/net/NetClient.cpp src/net/HostID.cpp src/net/ConferoNet.cpp bin/obj/confero1.0.0/ && $(COPY_FILE) --parents src/ui/ip.ui src/ui/confero.ui bin/obj/confero1.0.0/ && (cd `dirname bin/obj/confero1.0.0` && $(TAR) confero1.0.0.tar confero1.0.0 && $(COMPRESS) confero1.0.0.tar) && $(MOVE) `dirname bin/obj/confero1.0.0`/confero1.0.0.tar.gz . && $(DEL_FILE) -r bin/obj/confero1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: .qtSol/moc_confero.cpp .qtSol/moc_SciWrapper.cpp .qtSol/moc_DocumentManager.cpp .qtSol/moc_Chat.cpp .qtSol/moc_NetServer.cpp .qtSol/moc_NetManager.cpp .qtSol/moc_NetClientWriter.cpp .qtSol/moc_NetClient.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) .qtSol/moc_confero.cpp .qtSol/moc_SciWrapper.cpp .qtSol/moc_DocumentManager.cpp .qtSol/moc_Chat.cpp .qtSol/moc_NetServer.cpp .qtSol/moc_NetManager.cpp .qtSol/moc_NetClientWriter.cpp .qtSol/moc_NetClient.cpp
.qtSol/moc_confero.cpp: .qtSol/ui_confero.h \
		src/net/ConferoNet.h \
		src/net/SessionManager.h \
		src/net/Session.h \
		src/net/NetManager.h \
		src/net/NetServer.h \
		src/net/NetClient.h \
		src/net/PacketDefs.h \
		src/net/Packet.h \
		src/net/HostID.h \
		src/Random.h \
		src/document/SciWrapper.h \
		src/document/Edit.h \
		src/document/Document.h \
		src/document/DocumentManager.h \
		src/document/DocHolder.h \
		src/document/Chat.h \
		.qtSol/ui_ip.h \
		src/confero.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) src/confero.h -o .qtSol/moc_confero.cpp

.qtSol/moc_SciWrapper.cpp: src/net/ConferoNet.h \
		src/net/SessionManager.h \
		src/net/Session.h \
		src/net/NetManager.h \
		src/net/NetServer.h \
		src/net/NetClient.h \
		src/net/PacketDefs.h \
		src/net/Packet.h \
		src/net/HostID.h \
		src/Random.h \
		src/document/Edit.h \
		src/document/Document.h \
		src/document/SciWrapper.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) src/document/SciWrapper.h -o .qtSol/moc_SciWrapper.cpp

.qtSol/moc_DocumentManager.cpp: src/document/DocHolder.h \
		src/document/SciWrapper.h \
		src/net/ConferoNet.h \
		src/net/SessionManager.h \
		src/net/Session.h \
		src/net/NetManager.h \
		src/net/NetServer.h \
		src/net/NetClient.h \
		src/net/PacketDefs.h \
		src/net/Packet.h \
		src/net/HostID.h \
		src/Random.h \
		src/document/Edit.h \
		src/document/Document.h \
		src/document/Chat.h \
		.qtSol/ui_ip.h \
		src/document/DocumentManager.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) src/document/DocumentManager.h -o .qtSol/moc_DocumentManager.cpp

.qtSol/moc_Chat.cpp: src/document/Edit.h \
		src/net/ConferoNet.h \
		src/net/SessionManager.h \
		src/net/Session.h \
		src/net/NetManager.h \
		src/net/NetServer.h \
		src/net/NetClient.h \
		src/net/PacketDefs.h \
		src/net/Packet.h \
		src/net/HostID.h \
		src/Random.h \
		src/document/Chat.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) src/document/Chat.h -o .qtSol/moc_Chat.cpp

.qtSol/moc_NetServer.cpp: src/net/NetClient.h \
		src/net/SessionManager.h \
		src/net/Session.h \
		src/net/NetManager.h \
		src/net/NetServer.h \
		src/net/HostID.h \
		src/net/Packet.h \
		src/Random.h \
		src/net/PacketDefs.h \
		src/net/NetServer.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) src/net/NetServer.h -o .qtSol/moc_NetServer.cpp

.qtSol/moc_NetManager.cpp: src/net/NetServer.h \
		src/net/NetClient.h \
		src/net/SessionManager.h \
		src/net/Session.h \
		src/net/NetManager.h \
		src/net/HostID.h \
		src/net/Packet.h \
		src/Random.h \
		src/net/PacketDefs.h \
		src/net/NetManager.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) src/net/NetManager.h -o .qtSol/moc_NetManager.cpp

.qtSol/moc_NetClientWriter.cpp: src/net/NetClientWriter.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) src/net/NetClientWriter.h -o .qtSol/moc_NetClientWriter.cpp

.qtSol/moc_NetClient.cpp: src/net/SessionManager.h \
		src/net/Session.h \
		src/net/NetManager.h \
		src/net/NetServer.h \
		src/net/NetClient.h \
		src/net/PacketDefs.h \
		src/net/Packet.h \
		src/net/HostID.h \
		src/Random.h \
		src/net/NetClient.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) src/net/NetClient.h -o .qtSol/moc_NetClient.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: .qtSol/qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) .qtSol/qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all: .qtSol/ui_ip.h .qtSol/ui_confero.h
compiler_uic_clean:
	-$(DEL_FILE) .qtSol/ui_ip.h .qtSol/ui_confero.h
.qtSol/ui_ip.h: src/ui/ip.ui
	/usr/bin/uic-qt4 src/ui/ip.ui -o .qtSol/ui_ip.h

.qtSol/ui_confero.h: src/ui/confero.ui
	/usr/bin/uic-qt4 src/ui/confero.ui -o .qtSol/ui_confero.h

compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_uic_clean 

####### Compile

bin/obj/Random.o: src/Random.cpp src/Random.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o bin/obj/Random.o src/Random.cpp

bin/obj/main.o: src/main.cpp src/confero.h \
		.qtSol/ui_confero.h \
		src/net/ConferoNet.h \
		src/net/SessionManager.h \
		src/net/Session.h \
		src/net/NetManager.h \
		src/net/NetServer.h \
		src/net/NetClient.h \
		src/net/PacketDefs.h \
		src/net/Packet.h \
		src/net/HostID.h \
		src/Random.h \
		src/document/SciWrapper.h \
		src/document/Edit.h \
		src/document/Document.h \
		src/document/DocumentManager.h \
		src/document/DocHolder.h \
		src/document/Chat.h \
		.qtSol/ui_ip.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o bin/obj/main.o src/main.cpp

bin/obj/confero.o: src/confero.cpp src/confero.h \
		.qtSol/ui_confero.h \
		src/net/ConferoNet.h \
		src/net/SessionManager.h \
		src/net/Session.h \
		src/net/NetManager.h \
		src/net/NetServer.h \
		src/net/NetClient.h \
		src/net/PacketDefs.h \
		src/net/Packet.h \
		src/net/HostID.h \
		src/Random.h \
		src/document/SciWrapper.h \
		src/document/Edit.h \
		src/document/Document.h \
		src/document/DocumentManager.h \
		src/document/DocHolder.h \
		src/document/Chat.h \
		.qtSol/ui_ip.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o bin/obj/confero.o src/confero.cpp

bin/obj/SciWrapper.o: src/document/SciWrapper.cpp src/document/SciWrapper.h \
		src/net/ConferoNet.h \
		src/net/SessionManager.h \
		src/net/Session.h \
		src/net/NetManager.h \
		src/net/NetServer.h \
		src/net/NetClient.h \
		src/net/PacketDefs.h \
		src/net/Packet.h \
		src/net/HostID.h \
		src/Random.h \
		src/document/Edit.h \
		src/document/Document.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o bin/obj/SciWrapper.o src/document/SciWrapper.cpp

bin/obj/Edit.o: src/document/Edit.cpp src/document/Edit.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o bin/obj/Edit.o src/document/Edit.cpp

bin/obj/DocumentManager.o: src/document/DocumentManager.cpp src/document/DocumentManager.h \
		src/document/DocHolder.h \
		src/document/SciWrapper.h \
		src/net/ConferoNet.h \
		src/net/SessionManager.h \
		src/net/Session.h \
		src/net/NetManager.h \
		src/net/NetServer.h \
		src/net/NetClient.h \
		src/net/PacketDefs.h \
		src/net/Packet.h \
		src/net/HostID.h \
		src/Random.h \
		src/document/Edit.h \
		src/document/Document.h \
		src/document/Chat.h \
		.qtSol/ui_ip.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o bin/obj/DocumentManager.o src/document/DocumentManager.cpp

bin/obj/Document.o: src/document/Document.cpp src/document/Document.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o bin/obj/Document.o src/document/Document.cpp

bin/obj/DocHolder.o: src/document/DocHolder.cpp src/document/DocHolder.h \
		src/document/SciWrapper.h \
		src/net/ConferoNet.h \
		src/net/SessionManager.h \
		src/net/Session.h \
		src/net/NetManager.h \
		src/net/NetServer.h \
		src/net/NetClient.h \
		src/net/PacketDefs.h \
		src/net/Packet.h \
		src/net/HostID.h \
		src/Random.h \
		src/document/Edit.h \
		src/document/Document.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o bin/obj/DocHolder.o src/document/DocHolder.cpp

bin/obj/Chat.o: src/document/Chat.cpp src/document/Chat.h \
		src/document/Edit.h \
		src/net/ConferoNet.h \
		src/net/SessionManager.h \
		src/net/Session.h \
		src/net/NetManager.h \
		src/net/NetServer.h \
		src/net/NetClient.h \
		src/net/PacketDefs.h \
		src/net/Packet.h \
		src/net/HostID.h \
		src/Random.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o bin/obj/Chat.o src/document/Chat.cpp

bin/obj/SessionManager.o: src/net/SessionManager.cpp src/net/SessionManager.h \
		src/net/Session.h \
		src/net/NetManager.h \
		src/net/NetServer.h \
		src/net/NetClient.h \
		src/net/PacketDefs.h \
		src/net/Packet.h \
		src/net/HostID.h \
		src/Random.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o bin/obj/SessionManager.o src/net/SessionManager.cpp

bin/obj/Session.o: src/net/Session.cpp src/net/Session.h \
		src/net/SessionManager.h \
		src/net/NetManager.h \
		src/net/NetServer.h \
		src/net/NetClient.h \
		src/net/PacketDefs.h \
		src/net/Packet.h \
		src/net/HostID.h \
		src/Random.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o bin/obj/Session.o src/net/Session.cpp

bin/obj/Packet.o: src/net/Packet.cpp src/net/Packet.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o bin/obj/Packet.o src/net/Packet.cpp

bin/obj/NetServer.o: src/net/NetServer.cpp src/net/NetServer.h \
		src/net/NetClient.h \
		src/net/SessionManager.h \
		src/net/Session.h \
		src/net/NetManager.h \
		src/net/HostID.h \
		src/net/Packet.h \
		src/Random.h \
		src/net/PacketDefs.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o bin/obj/NetServer.o src/net/NetServer.cpp

bin/obj/NetManager.o: src/net/NetManager.cpp src/net/NetManager.h \
		src/net/NetServer.h \
		src/net/NetClient.h \
		src/net/SessionManager.h \
		src/net/Session.h \
		src/net/HostID.h \
		src/net/Packet.h \
		src/Random.h \
		src/net/PacketDefs.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o bin/obj/NetManager.o src/net/NetManager.cpp

bin/obj/NetClientWriter.o: src/net/NetClientWriter.cpp src/net/NetClientWriter.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o bin/obj/NetClientWriter.o src/net/NetClientWriter.cpp

bin/obj/NetClient.o: src/net/NetClient.cpp src/net/NetClient.h \
		src/net/SessionManager.h \
		src/net/Session.h \
		src/net/NetManager.h \
		src/net/NetServer.h \
		src/net/HostID.h \
		src/net/Packet.h \
		src/Random.h \
		src/net/PacketDefs.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o bin/obj/NetClient.o src/net/NetClient.cpp

bin/obj/HostID.o: src/net/HostID.cpp src/net/HostID.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o bin/obj/HostID.o src/net/HostID.cpp

bin/obj/ConferoNet.o: src/net/ConferoNet.cpp src/net/ConferoNet.h \
		src/net/SessionManager.h \
		src/net/Session.h \
		src/net/NetManager.h \
		src/net/NetServer.h \
		src/net/NetClient.h \
		src/net/PacketDefs.h \
		src/net/Packet.h \
		src/net/HostID.h \
		src/Random.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o bin/obj/ConferoNet.o src/net/ConferoNet.cpp

bin/obj/moc_confero.o: .qtSol/moc_confero.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o bin/obj/moc_confero.o .qtSol/moc_confero.cpp

bin/obj/moc_SciWrapper.o: .qtSol/moc_SciWrapper.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o bin/obj/moc_SciWrapper.o .qtSol/moc_SciWrapper.cpp

bin/obj/moc_DocumentManager.o: .qtSol/moc_DocumentManager.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o bin/obj/moc_DocumentManager.o .qtSol/moc_DocumentManager.cpp

bin/obj/moc_Chat.o: .qtSol/moc_Chat.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o bin/obj/moc_Chat.o .qtSol/moc_Chat.cpp

bin/obj/moc_NetServer.o: .qtSol/moc_NetServer.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o bin/obj/moc_NetServer.o .qtSol/moc_NetServer.cpp

bin/obj/moc_NetManager.o: .qtSol/moc_NetManager.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o bin/obj/moc_NetManager.o .qtSol/moc_NetManager.cpp

bin/obj/moc_NetClientWriter.o: .qtSol/moc_NetClientWriter.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o bin/obj/moc_NetClientWriter.o .qtSol/moc_NetClientWriter.cpp

bin/obj/moc_NetClient.o: .qtSol/moc_NetClient.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o bin/obj/moc_NetClient.o .qtSol/moc_NetClient.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

