#ifndef SYMBOL_H
#define SYMBOL_H
#include "QString"
class Symbol
{
    QString label;
    int address;
    bool equ;
public:
    Symbol();
    Symbol(QString);
    Symbol(QString,int);

    int getAddress();
    QString getLabel();
    bool getEqu();
    void setAddress(int addr);
    void setLabel(QString lbl);
    void setEqu(bool e);
};

#endif // SYMBOL_H
