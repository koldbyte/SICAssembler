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

void Instruction::setLine(unsigned int line){
    this->line = line;
}

void Instruction::setloc(unsigned int loc){
    this->loc = loc;
}

void Instruction::setObjectCode(unsigned long objc){
    this->ObjectCode = objc;
}

void Instruction::setLabel(QString label){
    this->label = label;
}

void Instruction::setOperator(QString oper){
    if(oper.startsWith("+")){
        oper.remove(0,1);
    }
    this->Operator = oper;
}

void Instruction::setOperand(QString operand){
    this->Operand = operand;
}

void Instruction::setBase_status(int bs){
    this->base_status = bs;
}

void Instruction::setFormat(int format){
    this->format = format;
}

bool Instruction::hasOperatorSet(){
    return !(Operator.isEmpty() || Operator.isNull());
}
