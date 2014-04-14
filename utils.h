#ifndef UTILS_H
#define UTILS_H
#include "QString"
#include "bits/stdc++.h"
class Utils
{
public:
    Utils();
    int convertOperand(QString s);
    int readOperand(QString s,int base = 10);
    int getStBytes(QString s);
    int uintToHexStr(unsigned int num,char* buff);
    QString expand(int value,int size);
    QString intToHexString(int i);
    QString base64_encode(QString string);
    QString base64_decode(QString string);

};

#endif // UTILS_H
