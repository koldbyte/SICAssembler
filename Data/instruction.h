#ifndef INSTRUCTION_H
#define INSTRUCTION_H
#include "QString"

class Instruction
{
    unsigned int line;
    unsigned int loc;
    unsigned long ObjectCode;
    QString label;
    QString Operator;
    QString Operand;
    int base_status;
    int format;
public:
    Instruction();
    Instruction(unsigned int line,unsigned int loc,unsigned long ObjectCode,QString label,QString Operator,QString Operand,int base_status,int format);

    unsigned int getLine();
    unsigned int getloc();
    unsigned long getObjectCode();
    QString getLabel();
    QString getOperator();
    QString getOperand();
    int getBase_status();
    int getFormat();

    setLine(unsigned int line);
    setloc(unsigned int loc);
    setObjectCode(unsigned long objc);
    setLabel(QString label);
    setOperator(QString oper);
    setOperand(QString operand);
    setBase_status(int bs);
    setFormat(int format);

    bool hasOperatorSet();

};

#endif // INSTRUCTION_H
