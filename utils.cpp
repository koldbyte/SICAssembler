#include "utils.h"

Utils::Utils(){
}

int Utils::convertOperand(QString s){
    QChar ch = s.at(0);
    if(ch=='#'){
        s = s.remove(0,1);
        return readOperand(s);
    }
    if(ch =='C'){
        return s.length() -3;
    }
    if(ch.isDigit()){
        return readOperand(s);
    }
    if(s.startsWith("X'") && s.endsWith("'")){
        s = s.remove(0,2);
        s.chop(1);
        return readOperand(s,16);
    }
    return 0;
}

int Utils::readOperand(QString s,int base){
    return s.toInt(0,base);
    //return (int) strtol(s.toStdString().c_str(), NULL,base);
}

int Utils::getStBytes(QString s) {
    if (s.at(0) == 'C')
        return s.length() - 3;
    if (s.at(0).isDigit()) {
        s = QString::number(s.toInt(),16);
        int val = s.length();
        return val / 2 + (val % 2);
    }
    if (s.startsWith("X'") && s.endsWith("'")) {
        int val = s.length() - 3;
        return val / 2 + (val % 2);
    }
    return 0;
}

int Utils::uintToHexStr(unsigned int num,char* buff){
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

QString Utils::expand(int value,int size){
    QString ret = QString::number(value,16);
    //qDebug() << "Expanded " << qPrintable(QString::number(value)) << " to " << qPrintable(ret);
    while(ret.length() < size) {
        ret = '0' + ret;
    }
    return ret;
}

QString Utils::intToHexString(int i) {
    std::stringstream ss;
    ss << std::hex << std::showbase << i;
    return QString::fromStdString(ss.str());
}

QString Utils::base64_encode(QString string){
    QByteArray ba;
    ba.append(string);
    return ba.toBase64();
}

QString Utils::base64_decode(QString string){
    QByteArray ba;
    ba.append(string);
    return QByteArray::fromBase64(ba);
}
