#ifndef OPCODE_H
#define OPCODE_H

class Opcode
{
    QString mnemonic;
    int format;
    int machinecode;
public:

    Opcode(QString,int,int);

    QString getMnemonic();
    int getFormat();
    int getMachinecode();
};

#endif // OPCODE_H
