#include "symtabmanager.h"
#include "registermanager.h"

SymtabManager::SymtabManager(){
    //Initialize Symbol Table with Registers
    RegisterManager *regM = &Singleton<RegisterManager>::Instance();
    int rcount = regM->getRegisterCount();
    for(int i=0;i<rcount;i++){
        Symbol sym = Symbol(regM->getRegister(i,0),regM->getAddress(i));
        insertSymbol(sym);
    }
}

Symbol SymtabManager::search(QString s){
    foreach (Symbol sym, m_symbols) {
        if(sym.getLabel()==s){
            return sym;
        }
    }
    return Symbol();
}

void SymtabManager::insertSymbol(Symbol sym){
    m_symbols.push_back(sym);
}

void SymtabManager::insertSymbol(QString lbl,int addr,bool equ){
    //check if label exists
    bool ok = true;
    foreach(Symbol sym , m_symbols){
        if(sym.getLabel().compare(lbl)==0){
            //error
            ok = false;
        }
    }
    if(ok){
        Symbol sym = Symbol(lbl,addr);
        sym.setEqu(equ);
        insertSymbol(sym);
    }
}


QVector<Symbol> SymtabManager::getAllSymbols(){
    return m_symbols;
}

void SymtabManager::ResetState(){
    m_symbols.clear();
    RegisterManager *regM = &Singleton<RegisterManager>::Instance();
    int rcount = regM->getRegisterCount();
    for(int i=0;i<rcount;i++){
        Symbol sym = Symbol(regM->getRegister(i,0),regM->getAddress(i));
        insertSymbol(sym);
    }
}
