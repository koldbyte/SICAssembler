#include "registermanager.h"
#include "QString"

RegisterManager::RegisterManager(){
    QString regs[] =  {"A","X","L","B","S","T","F"};
    int regcode[] = {0,1,2,3,4,5,6};
    int cnt_registers = sizeof(registers)/ sizeof(registers[0]);
    for(int i=0;i<cnt_registers;i++){
         insertRegister(regs[i],regcode[i]);
    }
}

int RegisterManager::getRegisterCount(){
    return m_registers.count();
}

int RegisterManager::getAddress(QString label){
    return m_registers[label];
}

int RegisterManager::getAddress(int i){
    if(i>=0 && i<=m_registers.size()){
        return m_registers.value(i);
    }else return -1;
}


QString RegisterManager::getLabel(int address){
    for(int i=0;i<m_registers.size();i++){
        if(m_registers.value(i)==address){
            return this->getRegister(i);
        }
    }
}

QString RegisterManager::getRegister(int i){
    if(i>=0 && i<=m_registers.size()){
        this->m_registers.key(i);
    }else return "";
}

RegisterManager::insertRegister(QString r,int a){
    if(r!="")
        m_registers.insert(r,a);
}

