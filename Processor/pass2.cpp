#include "pass2.h"

Pass2::Pass2(int startAddress) {
   this->startAddress = startAddress;
    BIT_E_3 = 0x1000;
    BIT_P_3 = 0x2000;
    BIT_B_3 = 0x4000;
    BIT_X_3 = 0x8000;
    BIT_I_3 = 0x10000;
    BIT_N_3 = 0x20000;

    BIT_E_4 = 0x100000;
    BIT_P_4 = 0x200000;
    BIT_B_4 = 0x400000;
    BIT_X_4 = 0x800000;
    BIT_I_4 = 0x1000000;
    BIT_N_4 = 0x2000000;
}

Instruction Pass2::doPass2(Instruction ins){
    SymtabManager *symMan = &Singleton<SymtabManager>::Instance();
    OptabManager *opMan = &Singleton<OptabManager>::Instance();
    RegisterManager *regMan = &Singleton<RegisterManager>::Instance();
    Utils *utils = &Singleton<Utils>::Instance();
    LittabManager *ltMan = &Singleton<LittabManager>::Instance();


    QString operand = ins.getOperand();
    QString oper = ins.getOperator();
    int com = opMan->getShiftedOpcode(oper);
    //qDebug() << "Pass2: Initialized com to " << qPrintable(QString::number(com,16));
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
        ins.setObjectCode(utils->convertOperand(operand));
        return ins;
    }
    if(oper.compare("WORD")==0){

    }
    if(oper.compare("LTORG")==0){
        //setobject code to littab
        ins.setObjectCode(ltMan->flushLtorg().toInt());
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
        if (!ins.isExtended()){
            //qDebug() << "Pass2: Not extended";
            com = objectFormat3(ins, com);
            //qDebug() << "Pass2: com set to " << qPrintable(QString::number(com,16));
        }else {
            //qDebug() << "Pass2: extended";
            com = objectFormat4(ins, com);
            //qDebug() << "Pass2: com set to " << qPrintable(QString::number(com,16));
        }
    }

    if(oper.compare("END")==0){
        ins.setObjectCode(ltMan->flushLtorg().toInt());
    }
    if(com == 0)
        return ins;
    ins.setObjectCode(com);
    return ins;
}

int Pass2::objectFormat4(Instruction v, int command){
    SymtabManager *symTab = &Singleton<SymtabManager>::Instance();
    Utils *utils = &Singleton<Utils>::Instance();
    ModTabManager *modMan = &Singleton<ModTabManager>::Instance();


    QString operand = v.getOperand();
    command = command << 8;
    command |= BIT_E_4;
    int address = 0;

    if (operand !=QString::null && operand.contains(",X")) {
        command |= BIT_X_4;
        operand = operand.left(operand.indexOf(","));

        address = symTab->getOperandValue(operand);
        int pc = v.getnextloc();
        address -= pc + 4;

        command += address;

    } else if (operand !=QString::null && operand.startsWith("#")) {
        command |= BIT_I_4;
        address = symTab->getOperandValue(operand.remove(0,1));
        command += address;
    } else if (operand !=QString::null && !operand.startsWith("#")) {
        command |= BIT_I_4;
        if (!v.isIndirectAddressing()) {
            command |= BIT_I_4;
        }
        if(v.isExtended()){
            command |= BIT_N_4;
        }
        address = symTab->getOperandValue(operand);
        if(startAddress == 0) {
            QString mod = "M" + utils->expand(v.getloc() + 1, 6) + "05";
            modMan->addMod(mod);
        }
        command += address;
    }
    return command;
}

int Pass2::objectFormat3(Instruction v, int command){
    SymtabManager *symTab = &Singleton<SymtabManager>::Instance();
    LittabManager *litman = &Singleton<LittabManager>::Instance();
    QString operand = v.getOperand();
    if(operand.startsWith('@')){
        v.setIndirectAddressing(true);
        operand = operand.remove(0,1);
    }
    qDebug() << "XXX" <<  qPrintable(QString::number(command,2)) << " " << qPrintable(operand.isEmpty() ? "Empty": "NotEmpty");
    int address = 0;
    qDebug() << "ObjectFormat3" << qPrintable(v.getOperator()) << qPrintable(v.getOperand())<<qPrintable("XX");
    if ((operand != QString::null || operand!="") && operand.contains(",X")) {
        //Indexed Mode addressing
        command |= BIT_X_3;
        command |= BIT_N_3;
        command |= BIT_I_3;
        qDebug() << qPrintable("1");
        operand = operand.left(operand.indexOf(","));
        address = symTab->getOperandValue(operand);
        int pc = v.getnextloc();
        //address = pc - address;
        address = address - pc;
        // command += address;
        command = pcOrBase(operand, command, address);
    } else if ((!operand.isEmpty()) && !operand.startsWith("#")) {
        // First of all try PC-relative,
        // If the offset is outside boundaries, start with the base.
        int dn;
        int pc = v.getnextloc();
        qDebug() << qPrintable("2");
        if(v.isOperandInLiteral()) {
            dn = litman->addressOfLiteral(operand);
        } else {
            dn = symTab->getOperandValue(operand);
        }

        int offset = dn - pc;
        qDebug() << qPrintable(QString::number(trimInt(offset)))<< qPrintable(QString::number(pc,10))<<qPrintable(QString::number(dn));
        // Bits N and I can also be 0...
        command |= BIT_N_3;
        if (!v.isIndirectAddressing()) {
            command |= BIT_I_3;
        }
        // command += trimInt(offset);
        command = pcOrBase(operand, command, offset);
        //if(offset < 0 ) command |=
    } else if ((operand != QString::null || operand!="") && operand.startsWith("#")) { // direct addressing
        command |= BIT_I_3; // bit I is set to 1
        operand = operand.remove(0,1);
        address = symTab->getOperandValue(operand);
qDebug() << qPrintable("3");
        if (symTab->hasLabel(operand) && !symTab->isEqu(operand)) {
            int pc = v.getnextloc();
            int offset = address - pc;
            command = pcOrBase(operand, command, offset);
        } else
            command += address;
    }else {
        qDebug() << qPrintable("4");
        command |= BIT_N_3;
        command |= BIT_I_3;

    }
    return command;
}

int Pass2::pcOrBase( QString operand, int command,int offset){
    int dn;
    SymtabManager *symTab = &Singleton<SymtabManager>::Instance();

    if (offset >= -2048 && offset <= 2047) {
        // PC-relative
        command |= BIT_P_3;

        command += trimInt(offset);
        //command += offset;

    } else {
        if (!isBase) {
            // Error
            qCritical()<< "Invalid offset, the base address can not be Single.\n";
        }

        dn = symTab->getOperandValue(operand);
        offset = dn - baseAddress;
        command |= BIT_B_3;
        command += trimInt(offset);

        if (!(offset >= 0 && offset <= 4095)) {
            qCritical() << "Invalid offset, the base address is Single.\n";
        }
    }
    return command;
}

int Pass2::trimInt(int i) {
    if (i >= 0)
        return i;

    QString s = QString::number( i, 2);
    qDebug() <<qPrintable("Trimint::") << qPrintable(s);
    //s = QString::fromStdString(s.toStdString().substr(s.length()-11));
    s = s.right(12);
    qDebug() <<qPrintable("Trimint::") << qPrintable(s);
    return s.toInt(0,2);
    //return QString::number(s.toInt(),2);
}

QString Pass2::convertedOperand(QString s) {
    Utils *utils= &Singleton<Utils>::Instance();

    QString ret = "";
    if (s.at(0) == 'C') {
        for (int i = 2; i < s.length() -1; ++i) {
            QChar c = s.at(i);
            ret += utils->intToHexString(c.digitValue());
        }
        return ret;
    }
    if (s.at(0).isDigit()) {
        return utils->intToHexString(s.toInt());
    }
    if (s.startsWith("X'") && s.endsWith("'")) {
        s = s.replace("'", "");
        s = s.replace("X", "");
        return s.toLower();
    }
    return ret;
}
