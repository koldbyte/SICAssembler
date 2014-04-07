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

Symbol::getAddress(){
    return this->address;
}

Symbol::getLabel(){
    return this->label;
}

Symbol::setAddress(int addr){
    this->address = addr;
}

Symbol::setLabel(QString lbl){
    this->label = lbl;
}

