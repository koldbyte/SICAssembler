#include "instruction.h"

Instruction::Instruction(){
    this->line=0;
    this->loc=0;
    this->ObjectCode="";
    this->label="";
    this->Operator="";
    this->Operand="";
    this->base_status=0;
    this->format=-1;
    this->isNull = false;
    this->valid = true;
    extended = false;
    indirectAddressing = false;
    operandInLiteral = false;
    error = "";
}

Instruction::Instruction(unsigned int line,unsigned int loc,QString ObjectCode,QString label,QString Operator,QString Operand,int base_status,int format){
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

QString Instruction::getObjectCode(){
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

void Instruction::setObjectCode(QString objc){
    this->isNull = false;
    this->ObjectCode = objc;
}

void Instruction::setObjectCode(int objectCode) {
    Utils *utils = &Singleton<Utils>::Instance();
    OptabManager *opMan = &Singleton<OptabManager>::Instance();

    int format = opMan->getOpcode(Operator).getFormat();

    switch( format ) {
        case 1:
            this->ObjectCode = utils->expand(objectCode, 2);
        break;
        case 2:
            this->ObjectCode = utils->expand(objectCode, 4);
        break;
        case 3:
            if(!extended)
                this->ObjectCode = utils->expand(objectCode, 6);
            else
                this->ObjectCode = utils->expand(objectCode, 8);
        break;
    }
}

void Instruction::setLabel(QString label){
    this->isNull = false;
    this->label = label;
}

void Instruction::setOperator(QString oper){
    this->isNull = false;
    if(oper.startsWith("+")){
        oper = oper.remove(0,1);
        this->setExtended(true);
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

bool Instruction::isOperandInLiteral() {
    return operandInLiteral;
}

bool Instruction::isExtended() {
    return extended;
}

void Instruction::setExtended(bool ext) {
    extended = ext;
}

bool Instruction::isIndirectAddressing(){
    return indirectAddressing;
}


Instruction Instruction::deserialize(QString readValue) {
        if(readValue == QString::null)
            return Instruction();

        QStringList columns = readValue.split("\\s+");
        Instruction *v = new Instruction();

        if(!columns[0].compare("N")==0)
            v->setLabel(columns[0]);

        v->setOperator(columns[1]);
        Utils *utils = &Singleton<Utils>::Instance();
        columns[2] = utils->base64_decode(columns[2]);
        qDebug() << "MAJORTEST "<<columns[3] << columns[4] << columns[5] << columns[6] << columns[7];
        if(!columns[2].compare("N")==0)
            v->setOperand(columns[2]);
        //v->setExtended(Boolean.getBoolean(columns[3]));
        //v->indirectAddressing = Boolean.getBoolean(columns[4]);
        v->setloc(columns[5].toUInt());
        //v->setValid(Boolean.getBoolean(columns[6]));
        //v->operandInLiteral = Boolean.parseBoolean(columns[7]);
        return *v;
    }

QString Instruction::serialize() {
    //Compose a row into a form suitable for recording in the intermediate file
    QString l = label;
    if(l == QString::null)
        l = "N";

    QString o = Operand;
    if(o == QString::null)
        o = "N";

    //You may encounter vicious loop, which we do not like, so encode...
    Utils *utils = &Singleton<Utils>::Instance();
    o = utils->base64_encode(o);

    return l + " " + this->Operator + " " + o + " " + this->extended + " " + this->indirectAddressing + " " + this->loc
    + " " + this->valid + " " + this->operandInLiteral;
}

void Instruction::setError(QString err){
    error = err;
}

QString Instruction::getError(){
    return error;
}
