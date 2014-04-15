#include "registermanager.h"
#include "QString"

RegisterManager::RegisterManager(){
    QString regs[] =  {"A","X","L","B","S","T","F"};
    int regcode[] = {0,1,2,3,4,5,6};
    int cnt_registers = sizeof(regs)/ sizeof(regs[0]);
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
        return (m_registers.begin()+i).value();
    }else
        return -1;
}


QString RegisterManager::getRegister(int address){
    for(m_it=m_registers.begin();m_it!=m_registers.end();m_it++){
        if(m_it.value()==address){
            return m_it.key();
        }
    }
    return QString::null;
}

QString RegisterManager::getRegister(int i,int c){
    c++;
    if(i>=0 && i<=m_registers.size()){
        return (this->m_registers.begin()+i).key();
    }
    return "";
}


void RegisterManager::insertRegister(QString r,int a){
    if(r!="")
        m_registers.insert(r,a);
}

