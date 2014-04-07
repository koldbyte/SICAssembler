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

    void setLine(unsigned int line);
    void setloc(unsigned int loc);
    void setObjectCode(unsigned long objc);
    void setLabel(QString label);
    void setOperator(QString oper);
    void setOperand(QString operand);
    void setBase_status(int bs);
    void setFormat(int format);

    bool hasOperatorSet();

};

#endif // INSTRUCTION_H
