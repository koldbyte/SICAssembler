#-------------------------------------------------
#
# Project created by QtCreator 2014-04-07T18:24:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MySICAssembler
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Managers/symtabmanager.cpp \
    Managers/optabmanager.cpp \
    Managers/registermanager.cpp \
    Managers/littabmanager.cpp \
    parser.cpp \
    Data/symbol.cpp \
    Data/opcode.cpp \
    Data/instruction.cpp \
    Data/literal.cpp \
    Gui/codeeditor.cpp \
    assembler.cpp \
    Gui/loggersingleton.cpp \
    utils.cpp \
    Data/objectfile.cpp \
    Managers/modtabmanager.cpp \
    Processor/pass1.cpp \
    Processor/pass2.cpp

HEADERS  += mainwindow.h \
    Managers/symtabmanager.h \
    Managers/optabmanager.h \
    Managers/registermanager.h \
    Managers/littabmanager.h \
    parser.h \
    Data/symbol.h \
    Data/opcode.h \
    Data/instruction.h \
    Data/literal.h \
    Singleton.h \
    Gui/codeeditor.h \
    assembler.h \
    Gui/loggersingleton.h \
    utils.h \
    Data/objectfile.h \
    Managers/modtabmanager.h \
    Processor/pass1.h \
    Processor/pass2.h

FORMS    += mainwindow.ui
