#ifndef INSTRUCTION_H
#define INSTRUCTION_H

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
};

#endif // INSTRUCTION_H
