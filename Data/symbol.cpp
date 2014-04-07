#include "symbol.h"
#include "QString"

Symbol::Symbol()
{
    label = "";
    address = -1;
}

Symbol::Symbol(QString lbl){
    this->label = lbl;
}

Symbol::Symbol(QString lbl , int addr){

    this->setAddress(addr);
}

int Symbol::getAddress(){
    return this->address;
}

QString Symbol::getLabel(){
    return this->label;
}

void Symbol::setAddress(int addr){
    this->address = addr;
}

void Symbol::setLabel(QString lbl){
    this->label = lbl;
}

