#ifndef PASS2_H
#define PASS2_H
#include "Data/instruction.h"
#include "Managers/littabmanager.h"
#include "Managers/modtabmanager.h"
#include "Managers/optabmanager.h"
#include "Managers/registermanager.h"
#include "Managers/symtabmanager.h"

class Pass2
{
    int startAddress;

    int baseAddress;
    bool isBase;
public:
    Pass2(int startAddress);
    Instruction doPass2(Instruction v);

    int objectFormat4(Instruction v, int com);
    int objectFormat3(Instruction v, int com);
    int pcOrBase( QString operand, int command,int offset);
    int trimInt(int i);
    QString convertedOperand(QString s);

    int BIT_E_3;
    int BIT_P_3;
    int BIT_B_3;
    int BIT_X_3;
    int BIT_I_3;
    int BIT_N_3;

    int BIT_E_4;
    int BIT_P_4;
    int BIT_B_4;
    int BIT_X_4;
    int BIT_I_4;
    int BIT_N_4;
};

#endif // PASS2_H
