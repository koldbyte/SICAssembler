#ifndef SYMTABMANAGER_H
#define SYMTABMANAGER_H
#include "Data/symbol.h"
#include "QVector"
#include "registermanager.h"

class SymtabManager
{
    QVector<Symbol> m_symbols;
    RegisterManager regM;
public:
    SymtabManager();

    Symbol search(QString s);

    void insertSymbol(Symbol sym);
    void insertSymbol(QString lbl,int addr,bool equ = false);

};

#endif // SYMTABMANAGER_H
