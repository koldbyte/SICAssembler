#include "parser.h"

Parser::Parser(){

}

bool Parser::checkquotes(QString s){
    if(!s.indexOf("'")<0) return true;
    return s.indexOf("'") != s.lastIndexOf("'") ;
}

Instruction Parser::parseLine(QString line){
    //no need to process empty lines
    if(line.isEmpty()) return Instruction();
    //check if the line is a comment line
    if(line.contains('.') && line.length()==1 || line.startsWith('.')){
        return Instruction();
    }
    //A line may have a comment in it..remove that comment
    int commentStartIndex = line.indexOf('.');
    if(commentStartIndex>0){
        line = line.left(commentStartIndex);
    }
    QStringList tokens = line.split("\\s+",QString::SkipEmptyParts);
    Instruction ins = Instruction();

    //Continue processing if there is a Operation specified
    if(tokens.length() > 1 || tokens[0].length()> 0){
        int counter = 0;
        OptabManager opm;
        foreach(QString token,tokens){
            if(token.length()==0)
                continue;
            //check if token is properly quoted otherwise include the
            if(!checkquotes(token)){
                tokens[counter] += " " + tokens[counter+1];
                token = tokens[counter];
                tokens[counter+1] = "";
            }

            switch(counter){
                case 0 : if(opm.isOpcode(token)){
                    ins.setOperator(token);
                }else ins.setLabel(token);
                break;
            case 1 : if(ins.hasOperatorSet()){
                    ins.setOperand(token);
                }else ins.setOperator(token);
                break;
                case 2 : ins.setOperand(token);break;
                default :
                    //error TODO
                break;
            }
            counter++;
        }
    }
    return ins;
}
