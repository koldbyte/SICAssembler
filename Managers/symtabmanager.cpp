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

void SymtabManager::addLabel(QString label, int locSt){
    if(hasLabel(label)) {
        qCritical() << "Error: Label " <<  label  <<  " is defined twice!";
    }

    insertSymbol(label,locSt);
}

bool SymtabManager::hasLabel(QString label){
    foreach (Symbol sym, m_symbols) {
        if(sym.getLabel()==label){
            return true;
        }
    }
    return false;
}

void SymtabManager::addEquals(QString label, int value){
    if(hasLabel(label)) {
        qCritical() << "Error: Label " <<  label  <<  " is defined twice!";
    }
    insertSymbol(label, value, true);
}

bool SymtabManager::isEqu(QString s) {
    return search(s).getEqu();
}

int SymtabManager::getloc(QString s){
    return search(s).getAddress();
}

int SymtabManager::getOperandValue(QString o) {
    if(hasLabel(o)) {
        return getloc(o);
    } else {
        int val = 0;
        val = o.toInt();
        return val;
    }
}
