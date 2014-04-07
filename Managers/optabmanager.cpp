#include "optabmanager.h"

OptabManager::OptabManager(){

}

void OptabManager::insertOpcode(Opcode op){
    this->m_optab.push_back(op);
}

void OptabManager::insertOpcode(QString Mnemonic,int format,int machinecode){
    Opcode op = Opcode(Mnemonic,format,machinecode);
    this->m_optab.push_back(op);
}

Opcode OptabManager::getOpcode(QString mnmemonic){
    for(int i=0;i<m_optab.size();i++){
        if(mnmemonic == m_optab[i].getMnemonic()){
            return getOpcode(i);
        }
    }
    return Opcode();
}

Opcode OptabManager::getOpcode(int i){
    if(i>=0 && i< m_optab.count()){
        return m_optab[i];
    }
    return Opcode();
}

bool OptabManager::isOpcode(QString op){
    if(op != QString::null && op.startsWith("+")){
        op = op.remove(0,1);
    }
    return (this->getOpcode(op).getMnemonic() != QString::null);
}




