#ifndef PARSER_H
#define PARSER_H
#include "Data/instruction.h"
#include "Data/symbol.h"
#include "Data/opcode.h"
#include "QString"
#include "QStringList"
#include "Managers/symtabmanager.h"
#include "Managers/optabmanager.h"

class Parser
{
    bool checkquotes(QString s);
public:
    Parser();
    Instruction parseLine(QString line);
};

#endif // PARSER_H
