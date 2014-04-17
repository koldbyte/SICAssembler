#include "parser.h"

Parser::Parser(){

}

bool Parser::checkquotes(QString s){
    //return true if quotes is proper
    if(s.indexOf("'")<0)
        return true;
    return s.indexOf("'") != s.lastIndexOf("'") ;
}

Instruction Parser::parseLine(QString line){
    //qDebug() << "Starting Parser on line :: " << qPrintable(line);

    //no need to process empty lines
    if(line.isEmpty() || line.isNull() || line.compare(" ")==0) return Instruction();

    //no need to process lines with comment only
    if((line.contains('.') && line.length()==1) || line.startsWith('.')){
        return Instruction();
    }

    //remove comment if any from the line
    int commentStartIndex = line.indexOf('.');
    if(commentStartIndex>0){
        line = line.left(commentStartIndex);
    }

    //Split the line into tokens
    //QStringList tokens = line.split(' ',QString::KeepEmptyParts);
    QRegExp rx("(\\s+)");
    QStringList tokens = line.split(rx,QString::KeepEmptyParts);
    qDebug() << "Parser: Split line into tokens :: size " << qPrintable(QString::number(tokens.size()))<< " -> " << qPrintable(tokens.join(','));

    Instruction ins = Instruction();

    //Continue processing if there is a Operation specified
    if(tokens.size() >= 1 || tokens[0].length()> 0){
        int counter = 0;
        OptabManager *opm = &Singleton<OptabManager>::Instance();

        foreach(QString token,tokens){
            //qDebug() << "Parsing token " << qPrintable(token) << " counter is" << qPrintable(QString::number(counter));
            if(token.length()==0)
                continue;

            //check if token is properly quoted otherwise include the
            if(!checkquotes(token)){
                tokens[counter] += " ";
                if(counter+1 < tokens.size()) tokens[counter] +=  tokens[counter+1];
                token = tokens[counter];
                if(counter+1 < tokens.size()) tokens[counter+1] = "";
            }

            switch(counter){
                case 0 : if(opm->isOpcode(token)){
                    qDebug() << "Parser : Token '"<< qPrintable(token)  << "' is Opcode.";
                    ins.setOperator(token);
                }else {
                    qDebug() << "Parser : Token '"<< qPrintable(token)  << "' is Label";
                    ins.setLabel(token);
                }
                break;
            case 1 : if(ins.hasOperatorSet()){
                    qDebug() << "Parser : Token '"<< qPrintable(token)  << "' is operand";
                    ins.setOperand(token);
                }else {
                    ins.setOperator(token);
                    qDebug() << "Parser : Token '"<< qPrintable(token)  << "' is Operator";
                }
                break;
                case 2 :  qDebug() << "Parser : Token '"<< qPrintable(token)  << "' is operand2"; ins.setOperand(token);break;
                default :
                    //error
                    ins.setError("Invalid No. of Operands!");
                    qCritical() << "Invalid No. of Operands!";
                break;
            }
            counter++;
        }
    }
    qDebug() <<"Parser: Complete! Result:: Operator-> " << qPrintable(ins.getOperator()) << "Operand-> " << qPrintable(ins.getOperand());
    return ins;
}
