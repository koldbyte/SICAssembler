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
        if (!ins.isExtended())
            com = objectFormat3(ins, com);
        else {
            com = objectFormat4(ins, com);
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
        // indeksno
        command |= BIT_X_4;
        operand = operand.left(operand.indexOf(","));

        address = symTab->getOperandValue(operand);
        int pc = v.getloc();
        address -= pc + 4;

        command += address;

    } else if (operand !=QString::null && operand.startsWith("#")) {
        //Direktno naslavljanje

        command |= BIT_I_4; // bit I is set to 1
        //address = symTab->getOperandValue(operand.substring(1));
        address = symTab->getOperandValue(operand.remove(0,1));

        command += address;
    } else if (operand !=QString::null && !operand.startsWith("#")) {
        //Neposredno naslavljanje

        command |= BIT_I_4; // bit I is set to 1

        if (!v.isIndirectAddressing()) {
            command |= BIT_I_4;
        }

        address = symTab->getOperandValue(operand);

        if(startAddress == 0) {
            //relocation
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

    //System.out.print("A-Fromat 3: " + Integer.toHexString(command) + " "
    //		+ v.getMnemonic() + " ");

    QString operand = v.getOperand();

    int address = 0;

    if (operand != QString::null && operand.contains(",X")) {
        //System.out.print("Indexno. ");
        // Indexno naslavljanje
        command |= BIT_X_3;

        // Bita N in I sta lahko tudi 0.
        command |= BIT_N_3;
        command |= BIT_I_3;

        operand = operand.left(operand.indexOf(","));

        address = symTab->getOperandValue(operand);
        int pc = v.getloc();
        address = pc - address;

        // System.out.print("address: " + address + " " + pc + " ");
        // Integer.toHexString(command) + " ");

        // command += address;

        command = pcOrBase(operand, command, address);

    } else if (operand !=QString::null && !operand.startsWith("#")) {
        // System.out.print("PC/Base ");
        // First of all try PC-relative,
        // If the offset is outside boundaries, start with the base.
        int dn;
        int pc = v.getloc();

        if(v.isOperandInLiteral()) {
            dn = litman->addressOfLiteral(operand);
            //System.out.println("address of literal " + dn);
        } else {
            dn = symTab->getOperandValue(operand);
        }

        // System.out.println(dn + " - " + pc);

        int offset = dn - pc;

        // Bits N and I can also be 0...
        command |= BIT_N_3;

        if (!v.isIndirectAddressing()) {
            command |= BIT_I_3;
        }

        // command += trimInt(offset);

        command = pcOrBase(operand, command, offset);

        // System.out.println("offset: " + offset);

    } else if (operand !=QString::null && operand.startsWith("#")) { // direct addressing
        // System.out.print("Direct");
        command |= BIT_I_3; // bit I is set to 1
        operand = operand.remove(0,1);
        address = symTab->getOperandValue(operand);

        if (symTab->hasLabel(operand) && !symTab->isEqu(operand)) {
            //int dn = symTab.getOperandValue(operand.substring(1));
            int pc = v.getloc();
            int offset = address - pc;

            command = pcOrBase(operand, command, offset);
        } else
            command += address;
    }
    return command;
}

int Pass2::pcOrBase( QString operand, int command,int offset){
    int dn;
    SymtabManager *symTab = &Singleton<SymtabManager>::Instance();

    // System.out.print(" offset: " + offset + " " +
    // Integer.toHexString(offset) + " ");

    if (offset >= -2048 && offset <= 2047) {
        // PC-relative
        command |= BIT_P_3;

        command += trimInt(offset);

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
    // System.out.println("offset " + offset);
    return command;
}

int Pass2::trimInt(int i) {
    if (i >= 0)
        return i;

    QString s = QString::number( i, 2);
    s = s.remove(0,s.length()-12);
    //s = s.substring(s.length() - 12);
    //return Integer.parseInt(s, 2);
    return QString::number(s.toInt(),2).toInt();
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
