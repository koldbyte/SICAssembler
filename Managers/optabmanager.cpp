#include "optabmanager.h"

OptabManager::OptabManager(){
    insertOpcode("ADD", 3, 0x18);
    insertOpcode("ADDF", 3, 0x58);
    insertOpcode("ADDR", 2, 0x90);
    insertOpcode("AND", 3, 0x40);
    insertOpcode("CLEAR", 2, 0xb4);
    insertOpcode("COMP", 3, 0x28);
    insertOpcode("COMPF", 3, 0x88);
    insertOpcode("COMPR", 2, 0xa0);
    insertOpcode("DIV", 3, 0x24);
    insertOpcode("DIVF", 3, 0x64);
    insertOpcode("DIVR", 2, 0x9c);
    insertOpcode("FIX", 1, 0xc4);
    insertOpcode("FLOAT", 1, 0xc0);
    insertOpcode("HIO", 1, 0xf4);
    insertOpcode("J", 3, 0x3c);
    insertOpcode("JEQ", 3, 0x30);
    insertOpcode("JGT", 3, 0x34);
    insertOpcode("JLT", 3, 0x38);
    insertOpcode("JSUB", 3, 0x48);
    insertOpcode("LDA", 3, 0x00);
    insertOpcode("LDB", 3, 0x68);
    insertOpcode("LDCH", 3, 0x50);
    insertOpcode("LDF", 3, 0x70);
    insertOpcode("LDL", 3, 0x08);
    insertOpcode("LDS", 3, 0x6c);
    insertOpcode("LDT", 3, 0x74);
    insertOpcode("LDX", 3, 0x04);
    insertOpcode("LPS", 3, 0xd0);
    insertOpcode("MUL", 3, 0x20);
    insertOpcode("MULF", 3, 0x60);
    insertOpcode("MULR", 2, 0x98);
    insertOpcode("NORM", 1, 0xc8);
    insertOpcode("OR", 3, 0x44);
    insertOpcode("RD", 3, 0xd8);
    insertOpcode("RMO", 2, 0xac);
    insertOpcode("RSUB", 3, 0x4c);
    insertOpcode("SHIFTL", 2, 0xa4);
    insertOpcode("SHIFTR", 2, 0xa8);
    insertOpcode("SIO", 1, 0xf0);
    insertOpcode("SSK", 3, 0xec);
    insertOpcode("STA", 3, 0x0c);
    insertOpcode("STB", 3, 0x78);
    insertOpcode("STCH", 3, 0x54);
    insertOpcode("STF", 3, 0x80);
    insertOpcode("STI", 3, 0xd4);
    insertOpcode("STL", 3, 0x14);
    insertOpcode("STS", 3, 0x7c);
    insertOpcode("STSW", 3, 0xe8);
    insertOpcode("STT", 3, 0x84);
    insertOpcode("STX", 3, 0x10);
    insertOpcode("SUB", 3, 0x1c);
    insertOpcode("SUBF", 3, 0x5c);
    insertOpcode("SUBR", 2, 0x94);
    insertOpcode("SVC", 2, 0xb0);
    insertOpcode("TD", 3, 0xe0);
    insertOpcode("TIO", 1, 0xf8);
    insertOpcode("TIX", 3, 0x2c);
    insertOpcode("TIXR", 2, 0xb8);
    insertOpcode("WD", 3, 0xdc);
    insertOpcode("RESW", -1, 0x0);
    insertOpcode("RESB", -1, 0x0);
    insertOpcode("WORD", -1, 0x0);
    insertOpcode("BYTE", -1, 0x0);
    insertOpcode("START", -1, 0x0);
    insertOpcode("END", -1, 0x0);
    insertOpcode("BASE", -1, 0x0);
    insertOpcode("NOBASE", -1, 0x0);
    insertOpcode("EQU", -1, 0x0);
    insertOpcode("LTORG", -1, 0x0);
    qDebug() << "Size of OPcode table is " << qPrintable(QString::number(m_optab.size()));
    qDebug() << "First Opcode " << qPrintable(m_optab[0].getMnemonic()) << qPrintable(QString::number(m_optab[0].getMachinecode()));
}

void OptabManager::insertOpcode(Opcode op){
    this->m_optab.push_back(op);
}

void OptabManager::insertOpcode(QString Mnemonic,int format,int machinecode){
    Opcode op = Opcode(Mnemonic,format,machinecode);
    this->m_optab.push_back(op);
    //qDebug() << "Inserting OPcode";
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

int OptabManager::getShiftedOpcode(QString mnemonic){
    Opcode op = getOpcode(mnemonic);
    int format = op.getFormat();
    if(format == 1 ) return op.getMachinecode();
    else if(format == 2 ) return op.getMachinecode() << 8;
    else if(format == 3 ) return op.getMachinecode() << 16;
    //TEST TODO
    else return op.getMachinecode();
}

bool OptabManager::isOpcode(QString op){
    if(op != QString::null && op.startsWith("+")){
        op = op.remove(0,1);
    }
    bool ret = true;
    Opcode pp = this->getOpcode(op);
    QString m = pp.getMnemonic();
    if(m.compare("")==0 || m.compare(QString::null)==0){
        ret = false;
    }
    return ret;
}




