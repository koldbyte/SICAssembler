#include "assembler.h"

Assembler::Assembler(){

}

void Assembler::Assemble(QString in){
    qDebug("Starting Assembler.");

    Parser *parser = &Singleton<Parser>::Instance();
    Instruction ins;
    QString line = "";
    QStringList all = in.split("\n");
    //QTextStream stream(in);
    int lines = 0;
    //while((line = stream.readLine())!= QString::null){
    foreach(QString line, all){
        lines++;

        qDebug() << "Running Parser on #" << qPrintable(QString::number(lines)) << "line :" << qPrintable(line);

        ins = parser->parseLine(line);

        qDebug() << "Parsed Line:: Found Instruction OPER" << qPrintable(ins.getOperator()) << " ObjectCode" << qPrintable(QString::number(ins.getObjectCode()));

        if(ins.Null()){
            ins = Instruction();
            obj.push_back(ins);
        }
        ins = this->pass1(ins);
        obj.push_back(ins);
    }

    qDebug() << "Pass1 Completed.. parsed total lines :" << qPrintable (QString::number(lines));
    qDebug() << "OBJ size" << qPrintable(QString::number(obj.size()));

    ins = pass2(ins,startAddress);
    lines = 0;
    foreach (Instruction i, obj) {
        lines++;
        if(!i.Null()){ //is valid
            i = pass2(i,0);
            //TODO verify this
            if(QString::number(i.getObjectCode()) != QString::null){
                code.push_back(this->prepareCode(i.getObjectCode(),i.getloc()));
            }else if(i.getOperator().compare("RESB")==0 || i.getOperator().compare("RESW")==0){
                //TODO Flush
            }
        }
        qDebug() << "Running pass2 on #" << qPrintable(QString::number(lines)) << "line. OPER: " <<  qPrintable(ins.getOperator());
    }
}

QString Assembler::prepareCode(unsigned long int oc,int l){
    QString ret = "";
    ret.append(QString::number(oc));
    ret.append(QString::number(l));
    return ret;
}

Instruction Assembler::pass1(Instruction ins){
    SymtabManager *symMan = &Singleton<SymtabManager>::Instance();
    OptabManager *opMan = &Singleton<OptabManager>::Instance();

    QString oper = ins.getOperator();

    if(oper.compare("START")==0){
        startAddress = (int) strtol(ins.getOperand().toStdString().c_str(), NULL, 16);
        ins.setloc(startAddress);
        ProgramName = ins.getLabel();
        return ins;
    }

    int loc = startAddress;
    if(oper.compare("END")!=0){
        QString label = ins.getLabel();
        if(oper.compare("EQU")==0){
            symMan->insertSymbol(label,(int) strtol(ins.getOperand().toStdString().c_str(), NULL,10),true);
        }else if(label != QString::null){
            symMan->insertSymbol(label,loc);
        }//else if()
        //add to literal table
        //-------
        startAddress = loc;
        if(oper.compare("RESW")==0){
            loc += 3*(convertOperand(ins.getOperand()));
        }else if(oper.compare("RESB")==0){
            loc += convertOperand(ins.getOperand());
        }else if(oper.compare("BYTE")==0){
            loc += convertOperand(ins.getOperand());
        }else if(oper.compare("WORD")==0){
            loc += 3;
        }else if(oper.compare("LTORG")==0){
            //TODO get location from literals
            //loc =
        }else if(opMan->isOpcode(oper)){
            int format = opMan->getOpcode(oper).getFormat();
            if(format !=-1){
                loc += format;
                //ADD isEXtended TODO
                //if extended add 1 to loc
            }
        }else{
            //error TODO
        }
    }else{
        //TODO update loc using literal table.
    }
    startAddress = loc;
    ins.setloc(loc);
    //TODO OUtput log to console here
    return ins;
}


Instruction Assembler::pass2(Instruction ins,int sA = 0){
    int startAddress2 = sA;
    int baseAddress;
    bool isBase = false;

    SymtabManager *symMan = &Singleton<SymtabManager>::Instance();
    OptabManager *opMan = &Singleton<OptabManager>::Instance();
    RegisterManager *regMan = &Singleton<RegisterManager>::Instance();

    QString operand = ins.getOperand();
    QString oper = ins.getOperator();
    int com = opMan->getShiftedOpcode(oper);

    if(oper.compare("BASE")==0){
       isBase = true;
       baseAddress = symMan->search(operand).getAddress();
       return ins;
    }
    if(oper.compare("NOBASE")==0){
        isBase = false;
        return ins;
    }
    if(oper.compare("BYTE")==0){
        ins.setObjectCode(convertOperand(operand));
        return ins;
    }
    if(oper.compare("WORD")==0){

    }
    if(oper.compare("LTORG")==0){
        //TODO : setobject code to littab
    }

    int format = opMan->getOpcode(oper).getFormat();
    if(format == 2){
        if(operand.contains(",")){
            QStringList o = operand.split(",");
            com += regMan->getAddress(o[0]) << 4;
            com += regMan->getAddress(o[1]);
        }else{
            com += regMan->getAddress(operand) << 4;
        }
    }else if(format == 3){
        //TODO
        //isextended related.
    }

    if(oper.compare("END")==0){
        //todo set object code using littab
    }
    if(com == 0) return ins;
    ins.setObjectCode(com);
    return ins;
}


int Assembler::convertOperand(QString s){
    QChar ch = s.at(0);
    if(ch=='#'){
        return readOperand(s.remove(0,1),10);
    }
    if(ch =='C'){
        return s.length() -3;
    }
    if(ch.isDigit()){
        return readOperand(s,10);
    }
    if(s.startsWith("X'") && s.endsWith("'")){
        s.remove(0,2).chop(1);
        return readOperand(s,16);
    }
    return 0;
}

int Assembler::readOperand(QString s,int base = 10){
    return (int) strtol(s.toStdString().c_str(), NULL,base);
}

QList<QString> Assembler::getCode(){
    return this->code;
}

