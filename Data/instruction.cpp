#include "instruction.h"

Instruction::Instruction()
{


}

Instruction::Instruction(unsigned int line,unsigned int loc,unsigned long ObjectCode,QString label,QString Operator,QString Operand,int base_status,int format){
    this->line=line;
    this->loc=loc;
    this->ObjectCode=ObjectCode;
    this->label=label;
    this->Operator=Operator;
    this->Operand=Operand;
    this->base_status=base_status;
    this->format=format;

}

unsigned int Instruction::getLine(){
    return this->line;
}

unsigned int Instruction::getloc(){
    return this->loc;
}

unsigned long Instruction::getObjectCode(){
    return this->ObjectCode;
}

QString Instruction::getLabel(){
    return this->label;
}

QString Instruction::getOperator(){
    return this->Operator;
}

QString Instruction::getOperand(){
    return this->Operand;
}

int Instruction::getBase_status(){
    return this->base_status;
}

int Instruction::getFormat(){
    return this->format;
}
