#ifndef INSTRUCTION_H
#define INSTRUCTION_H
#include "QString"
#include "QStringList"
#include "QDebug"
#include "utils.h"
#include "Singleton.h"
#include "Managers/optabmanager.h"
class Instruction
{
    unsigned int line;
    unsigned int loc;
    QString ObjectCode;
    QString label;
    QString Operator;
    QString Operand;
    int base_status;
    int format;
    int isNull;
    bool extended;
    bool valid;
    bool indirectAddressing;
    bool operandInLiteral;
public:
    Instruction();
    Instruction(unsigned int line,unsigned int loc,QString ObjectCode,QString label,QString Operator,QString Operand,int base_status,int format);

    unsigned int getLine();
    unsigned int getloc();
    QString getObjectCode();
    QString getLabel();
    QString getOperator();
    QString getOperand();
    int getBase_status();
    int getFormat();
    bool isOperandInLiteral();
    bool isExtended();
    bool isIndirectAddressing();

    void setLine(unsigned int line);
    void setloc(unsigned int loc);
    void setObjectCode(QString objc);
    void setObjectCode(int objectCode);
    void setLabel(QString label);
    void setOperator(QString oper);
    void setOperand(QString operand);
    void setBase_status(int bs);
    void setFormat(int format);
    void setExtended(bool ext);

    bool hasOperatorSet();
    bool Null();

    Instruction deserialize(QString readValue);
    QString serialize();
};

#endif // INSTRUCTION_H
