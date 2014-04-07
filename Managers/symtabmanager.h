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
    Symbol search(QString s,int l,int h);

    insertSymbol(Symbol sym);
    insertSymbol(QString lbl,int addr);

};

#endif // SYMTABMANAGER_H
