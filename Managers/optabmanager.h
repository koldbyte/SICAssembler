#ifndef OPTABMANAGER_H
#define OPTABMANAGER_H
#include "Data/opcode.h"
#include "QVector"
#include "QString"

class OptabManager
{
    QVector<Opcode> m_optab;

public:
    OptabManager();

    insertOpcode(Opcode op);
    insertOpcode(QString Mnemonic,int format,int machinecode);

    Opcode getOpcode(QString mnmemonic);
    Opcode getOpcode(int i);

    bool isOpcode(QString op);
};

#endif // OPTABMANAGER_H
