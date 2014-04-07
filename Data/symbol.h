#ifndef SYMBOL_H
#define SYMBOL_H

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
    setAddress(int);
    setLabel(QString);
};

#endif // SYMBOL_H
