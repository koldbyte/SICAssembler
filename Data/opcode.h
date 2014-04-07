#ifndef OPCODE_H
#define OPCODE_H
#include "QString"

class Opcode
{
    QString mnemonic;
    int format;
    int machinecode;
public:
    Opcode();
    Opcode(QString,int,int);

    QString getMnemonic();
    int getFormat();
    int getMachinecode();
};

#endif // OPCODE_H
