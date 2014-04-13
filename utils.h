#ifndef UTILS_H
#define UTILS_H
#include "QString"
class Utils
{
public:
    Utils();
    int convertOperand(QString s);
    int readOperand(QString s,int base = 10);
    int getStBytes(QString s);
    int uintToHexStr(unsigned int num,char* buff);

};

#endif // UTILS_H
