#include "pass1.h"

Pass1::Pass1(){

}

Instruction Pass1::doPass1(Instruction ins){
    SymtabManager *symMan = &Singleton<SymtabManager>::Instance();
    OptabManager *opMan = &Singleton<OptabManager>::Instance();
    Utils *utils = &Singleton<Utils>::Instance();
    LittabManager *ltMan = &Singleton<LittabManager>::Instance();

    QString oper = ins.getOperator();

    if(oper.compare("START")==0){
        //Start address in the source program is given as Hex...store it as decimal.
        //startAddress = (int) strtol(ins.getOperand().toStdString().c_str(), NULL, 16);
        StartAddress = utils->readOperand(ins.getOperand(),16);
        //StartAddress = QString::number(ins.getOperand().toInt(),16).toInt();
        oldLocSt = StartAddress;
        ins.setloc(StartAddress);
        programName = ins.getLabel();
        return ins;
    }

    int loc = oldLocSt;
    ins.setloc(loc);

    if(oper.compare("END")!=0){
        QString label = ins.getLabel();
        if(oper.compare("EQU")==0){
            //symMan->insertSymbol(label,(int) strtol(ins.getOperand().toStdString().c_str(), NULL,16),true);
            symMan->insertSymbol(label,ins.getOperand().toInt(0,16),true);
        }else if(label != QString::null){
            symMan->insertSymbol(label,loc);
        }else if(ins.isOperandInLiteral()){
            ltMan->addLiteral(label,ins.getOperand());
        }
        oldLocSt = loc;
        if(oper.compare("RESW")==0){
            loc += 3*(utils->convertOperand(ins.getOperand()));
        }else if(oper.compare("RESB")==0){
            loc += utils->convertOperand(ins.getOperand());
        }else if(oper.compare("BYTE")==0){
            //loc += utils->convertOperand(ins.getOperand());
            loc += utils->getStBytes(ins.getOperand());
        }else if(oper.compare("WORD")==0){
            loc += 3;
        }else if(oper.compare("LTORG")==0){
            // get location from literals
            loc = ltMan->processLtorg(loc);
        }else if(opMan->isOpcode(oper)){
            int format = opMan->getOpcode(oper).getFormat();
            if(format !=-1){
                loc += format;
                //if extended add 1 to loc
                if(ins.isExtended())
                    loc+=1;
            }
        }else{
            //error
            ins.setError("Invalid Operator " + oper);
            qCritical()<< "Invalid Operator "  << oper;
        }
    }else{
        //update loc using literal table.
        loc = ltMan->processLtorg(loc);
    }
    oldLocSt = loc;
    //ins.setloc(loc);
    ins.setnextloc(loc);
    //TODO OUtput log to console here
    qDebug() << "Pass 1: " << ins.getOperator() << " "  << utils->intToHexString(ins.getloc());
    return ins;
}

int Pass1::getLength() {
    return oldLocSt - StartAddress;
}

int Pass1::getInitialAddress() {
    return StartAddress;
}

QString Pass1::getProgramName() {
    return programName;
}
