#include "assembler.h"

Assembler::Assembler(){
    programLength = 0;
    ProgramName = "";
    programObjectData = "";
}

void Assembler::Assemble(QString in){
    qDebug("Starting Assembler.");
    Parser *parser = &Singleton<Parser>::Instance();
    Instruction ins;
    int lines = 0;
    QStringList all = in.split("\n");
    Pass1 *p1 = new Pass1();

    foreach(QString line, all){
        lines++;

        qDebug() << "Running Parser on #" << qPrintable(QString::number(lines)) << "line :" << qPrintable(line);
        ins = parser->parseLine(line);
        if(!ins.Null()) qDebug() << "Parsed Line:: Found Instruction: Operator->" << qPrintable(ins.getOperator()) << " Operand->" << qPrintable(ins.getOperand());
        else qDebug() << "Parsed Line:: Empty or Commented Line";

        if(ins.Null()){
            //ins = Instruction();
            //obj.push_back(ins);
            continue;
        }
        qDebug() << "Pass1: Running on instruction : Operator->" << qPrintable(ins.getOperator()) << " Operator->" << qPrintable(ins.getOperand());
        ins = p1->doPass1(ins);
        //qDebug() << "Pass1: Returned instruction: Operator->" << qPrintable(ins.getOperator()) << " Operand->" << qPrintable(ins.getOperand());

        obj.push_back(ins);
    }

    qDebug() << "Pass1: Completed! Parsed total lines " << qPrintable (QString::number(lines));
    //qDebug() << "OBJ size" << qPrintable(QString::number(obj.size()));
    qDebug() << "Pass1: Initial Address set to (HEX)" << qPrintable(QString::number(p1->getInitialAddress(),16));

    Pass2 *p2 = new Pass2(p1->getInitialAddress());
    ObjectFile *objData = new ObjectFile();

    objData->writeHeader(p1->getLength(),p1->getProgramName(), p1->getInitialAddress());

    lines = 0;
    QList<Instruction> ::iterator it;
    for(it= obj.begin();it!=obj.end();it++){
        lines++;
        qDebug() << "Pass2: Running on instruction: Operator->" << qPrintable((*it).getOperator()) << " Operand->" << qPrintable((*it).getOperand());
        if(!(*it).Null()){ //is valid
            *it = p2->doPass2(*it);
            qDebug() << "Pass2: Returned instruction: Operator" << qPrintable((*it).getOperator())<< " Operand->" << qPrintable((*it).getOperand()) << " ObjectCode->" << qPrintable((*it).getObjectCode());
            if((*it).getOperator().compare("RESB")==0 || (*it).getOperator().compare("RESW")==0){
                objData->flush(it->getloc());
            }else if((*it).getObjectCode() != QString::null || (*it).getObjectCode() != ""){
                objData->write(it->getObjectCode(), it->getloc());
            }
        }
    }
    objData->writeEndOP(p1->getInitialAddress());
    this->programObjectData = objData->getFinal();
    qDebug() << "Processing of Source Code Complete!";
}


QString Assembler::getFinalCode(){
    return this->programObjectData;
}


QList<Instruction> Assembler::getAllInstructions(){
    return this->obj;
}

void Assembler::ResetState(){
    programLength = 0;
    ProgramName = "";
    obj.clear();
    startAddress = 0;
}
