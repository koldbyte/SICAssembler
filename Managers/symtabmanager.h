#ifndef SYMTABMANAGER_H
#define SYMTABMANAGER_H
#include "Data/symbol.h"
#include "QVector"
#include "registermanager.h"
#include "QDebug"

class SymtabManager
{
    QVector<Symbol> m_symbols;
    RegisterManager regM;
public:
    SymtabManager();
    void ResetState();
    Symbol search(QString s);
    bool hasLabel(QString label);
    bool isEqu(QString s);
    int getOperandValue(QString o);
    int getloc(QString s);


    void addLabel(QString label, int locSt);
    void addEquals(QString label, int value);

    void insertSymbol(Symbol sym);
    void insertSymbol(QString lbl,int addr,bool equ = false);

    QVector<Symbol> getAllSymbols();

};

#endif // SYMTABMANAGER_H
