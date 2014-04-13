#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <sstream>
#include <iomanip>
#include "Singleton.h"
#include "parser.h"
#include "utils.h"
#include "QTextStream"
#include "QList"
#include "Data/instruction.h"
#include "Managers/symtabmanager.h"
#include "mainwindow.h"
#include "QDebug"
class Assembler
{
    QList<Instruction> obj;
    QList<QString> code;
    int startAddress;
    QString ProgramName;
    int programLength;
    int uintToHexStr(unsigned int num,char* buff);

public:
    Assembler();
    void ResetState();
    void Assemble(QString in);
    Instruction pass1(Instruction ins);
    Instruction pass2(Instruction ins,int sA);

    int convertOperand(QString s);
    int readOperand(QString s,int base);
    QString prepareCode(unsigned long int oc,int l);
    QList<QString> getCode();
    QString prepareHeaderCode();

    QList<Instruction> getAllInstructions();
};

#endif // ASSEMBLER_H
