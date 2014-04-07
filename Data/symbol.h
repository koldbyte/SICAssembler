#ifndef SYMBOL_H
#define SYMBOL_H
#include "QString"
class Symbol
{
    QString label;
    int address;
public:
    Symbol();
    Symbol(QString);
    Symbol(QString,int);

    int getAddress();
    QString getLabel();
    void setAddress(int addr);
    void setLabel(QString lbl);
};

#endif // SYMBOL_H
