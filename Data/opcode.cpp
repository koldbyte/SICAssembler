#include "opcode.h"


Opcode::Opcode(){
    this->mnemonic  = "";
    this->format = -1;
    this->machinecode = -1;
}

Opcode::Opcode(QString m, int f, int mc)
{
    this->mnemonic  = m;
    this->format = f;
    this->machinecode = mc;
}

QString Opcode::getMnemonic(){
    return this->mnemonic;
}

int Opcode::getFormat(){
    return this->format;
}

int Opcode::getMachinecode(){
    return this->machinecode;
}
