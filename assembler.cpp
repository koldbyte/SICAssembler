#include "assembler.h"

Assembler::Assembler(){
    programLength = 0;
    ProgramName = "";
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

    //ins = pass2(ins,startAddress);
    lines = 0;
    QList<Instruction> ::iterator it;
    for(it= obj.begin();it!=obj.end();it++){
    //foreach (Instruction i, obj) {
        lines++;
        qDebug() << "Pass2: Starting on instruction :: OPER" << qPrintable((*it).getOperator()) << " ObjectCode" << qPrintable(QString::number((*it).getObjectCode()));
        if(!(*it).Null()){ //is valid
            *it = pass2(*it,0);
            qDebug() << "Pass2: Returned instruction :: OPER" << qPrintable((*it).getOperator()) << " ObjectCode" << qPrintable(QString::number((*it).getObjectCode()));
            //TODO verify this
            if(QString::number((*it).getObjectCode()) != QString::null){
                code.push_back(this->prepareCode((*it).getObjectCode(),(*it).getloc()));
            }else if((*it).getOperator().compare("RESB")==0 || (*it).getOperator().compare("RESW")==0){
                //TODO Flush
            }
        }
    }
}

int Assembler::uintToHexStr(unsigned int num,char* buff){
    char hex [] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' ,'A', 'B', 'C', 'D', 'E', 'F' };
    int len=0,k=0;
    do//for every 4 bits
    {
        //get the equivalent hex digit
        buff[len] = hex[num & 0xF];
        len++;
        num>>=4;
    }while(num!=0);
    //since we get the digits in the wrong order reverse the digits in the buffer
    for(;k<len/2;k++)
    {//xor swapping
        buff[k]^=buff[len-k-1];
        buff[len-k-1]^=buff[k];
        buff[k]^=buff[len-k-1];
    }
    //null terminate the buffer and return the length in digits
    buff[len]='\0';
    return len;
}

QString Assembler::prepareCode(unsigned long int oc,int l){
    char buff[16];
    int length;
    length = this->uintToHexStr(oc,buff);
    std::string a = buff;
    QString aa = QString::fromStdString(a);

    length = this->uintToHexStr(l,buff);
    std::string b = buff;
    QString bb = QString::fromStdString(b);

    QString ret = "";
    ret.append(aa);
    ret.append(",");
    ret.append(bb);
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

QString Assembler::prepareHeaderCode(){
    OptabManager *opMan = &Singleton<OptabManager>::Instance();

    QString ret = "";
    int locctr = 0;
    bool tt = false;
    QString tblock = "";
    QString tblock1 = "";
    int start=0;
    int finish=0;
    QList<Instruction> ::iterator it;
    for(it= obj.begin();it!=obj.end();it++){
        Instruction i = *it;
    //foreach(Instruction i, obj){
        QString oper = i.getOperator();
        std::stringstream ss;
        ss.flush();
        if(oper.compare("START")==0){
            ss << "H^" <<std::left<<std::setw(6)<<ProgramName.toStdString()<<"^"<<std::right<<std::setw(6)<<std::setfill('0')<<std::hex<<startAddress<<"^"<<std::setw(6)<<std::setfill('0')<<std::hex<<programLength<<std::endl;
            ret += QString::fromStdString(ss.str());
            ss.flush();
        }else{
            qDebug() << "Instruction Oper" << qPrintable(oper) << "has loc value " << qPrintable(QString::number(i.getloc())) <<" and format " << qPrintable(QString::number(i.getFormat()));
            if(i.getloc() - start <= 30){
                if(!tt){
                    tblock.clear();
                    ss.flush();
                    ss <<"T^"<<std::hex<<std::setw(6)<<std::setfill('0')<< start;//a portion is remaining
                    ret += QString::fromStdString(ss.str());
                    ss.flush();
                    tt = true;
                }else{
                    ss.flush();
                    int format = i.getFormat();
                    if(format==-1) format = opMan->getOpcode(oper).getFormat();
                    qDebug() << "Correct Format to " << qPrintable(QString::number(format)) << " Obj--> " << qPrintable(QString::number(i.getObjectCode()));
                    if(format==1)
                        ss <<"^"<<std::setw(2)<<std::hex<<i.getObjectCode();
                    else if(format==2)
                        ss <<"^"<<std::setw(4)<<std::hex<<i.getObjectCode();
                    else if(format==3)
                        ss <<"^"<<std::setw(4)<<std::hex<<i.getObjectCode();
                    else if(format==4)
                        ss <<"^"<<std::setw(8)<<std::hex<<i.getObjectCode();
                    tblock1 += QString::fromStdString(ss.str());
                    ss.flush();
                }
                locctr += i.getloc();
            }else{
                //single tblock is complete
                //so append it to header
                finish = i.getloc();
                ss.flush();
                ss <<"^"<<std::setw(2)<<std::hex<<(finish - start);
                ret += QString::fromStdString(ss.str());
                ss.flush();
                ret += tblock1+"\n";
                //start a new tblock
                tblock.clear();
                tblock1.clear();
                tt = true;
                locctr = 0;
                start = i.getloc();
                ss <<"T^"<<std::hex<<std::setw(6)<<std::setfill('0')<< start;//a portion is remaining
                ret += QString::fromStdString(ss.str());
                ss.flush();
                locctr += i.getloc();
            }
        }
        qDebug() << qPrintable(tblock) << " || " << qPrintable(tblock1);
    }
    return ret;
}


QList<Instruction> Assembler::getAllInstructions(){
    return this->obj;
}

void Assembler::ResetState(){
    programLength = 0;
    ProgramName = "";
    obj.clear();
    code.clear();
    startAddress = 0;
}
