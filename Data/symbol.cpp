#include "symbol.h"
#include "QString"

Symbol::Symbol()
{
    label = "";
    address = -1;
    equ = false;
}

Symbol::Symbol(QString lbl){
    this->label = lbl;
}

Symbol::Symbol(QString lbl , int addr){
    this->setLabel(lbl);
    this->setAddress(addr);
}

int Symbol::getAddress(){
    return this->address;
}

QString Symbol::getLabel(){
    return this->label;
}

bool Symbol::getEqu(){
    return this->equ;
}

void Symbol::setAddress(int addr){
    this->address = addr;
}

void Symbol::setLabel(QString lbl){
    this->label = lbl;
}

void Symbol::setEqu(bool e){
    this->equ = e;
}
