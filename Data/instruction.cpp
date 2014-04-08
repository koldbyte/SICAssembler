#include "instruction.h"

Instruction::Instruction()
{
    this->line=0;
    this->loc=0;
    this->ObjectCode=0;
    this->label="";
    this->Operator="";
    this->Operand="";
    this->base_status=0;
    this->format=-1;
    this->isNull = false;

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
    this->isNull = false;
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

void Instruction::setLine(unsigned int line){
    this->isNull = false;
    this->line = line;
}

void Instruction::setloc(unsigned int loc){
    this->isNull = false;
    this->loc = loc;
}

void Instruction::setObjectCode(unsigned long objc){
    this->isNull = false;
    this->ObjectCode = objc;
}

void Instruction::setLabel(QString label){
    this->isNull = false;
    this->label = label;
}

void Instruction::setOperator(QString oper){
    this->isNull = false;
    if(oper.startsWith("+")){
        oper.remove(0,1);
    }
    this->Operator = oper;
}

void Instruction::setOperand(QString operand){
    this->isNull = false;
    this->Operand = operand;
}

void Instruction::setBase_status(int bs){
    this->base_status = bs;
    this->isNull = false;
}

void Instruction::setFormat(int format){
    this->isNull = false;
    this->format = format;
}

bool Instruction::hasOperatorSet(){
    return !(Operator.isEmpty() || Operator.isNull());
}

bool Instruction::Null(){
    return isNull;
}
