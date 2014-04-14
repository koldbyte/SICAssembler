#ifndef PASS1_H
#define PASS1_H
#include "Data/instruction.h"
#include "Managers/littabmanager.h"
#include "Managers/symtabmanager.h"
#include "Managers/optabmanager.h"

class Pass1
{
    int StartAddress, oldLocSt;
    QString programName;
public:
    Pass1();
    Instruction doPass1(Instruction ins);
    int getLength();
    int getInitialAddress();
    QString getProgramName();
};

#endif // PASS1_H
