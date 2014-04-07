#include "optabmanager.h"

OptabManager::OptabManager(){

}

OptabManager::insertOpcode(Opcode op){
    this->m_optab.push_back(op);
}

OptabManager::insertOpcode(QString Mnemonic,int format,int machinecode){
    Opcode op = Opcode(Mnemonic,format,machinecode);
    this->m_optab.push_back(op);
}

Opcode OptabManager::getOpcode(QString mnmemonic){
    for(int i=0;i<m_optab.size();i++){
        if(mnmemonic == m_optab[i].getMnemonic()){
            return getOpcode(i);
        }
    }
    return null;
}

Opcode OptabManager::getOpcode(int i){
    if(i>=0 && i< m_optab.count()){
        return m_optab[i];
    }
    return null;
}

bool OptabManager::isOpcode(QString op){
    if(op !=null && op.startsWith("+")){
        op = op.remove(0,1);
    }
    return this->getOpcode(op) != null;
}




