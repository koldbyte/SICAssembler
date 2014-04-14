#include "literal.h"
#include "QIntegerForSize"
Literal::Literal(){
    ltorgDump = -1;
    location = -1;
}

QString Literal::getValue() {
    Utils *utils = &Singleton<Utils>::Instance();
    return utils->expand(value, length * 2);
}

void Literal::setValue(int value) {
    this->value = value;
}

int Literal::getLength() {
    return this->length;
}

void Literal::setLength(int length) {
    this->length = length;
}

int Literal::getLocation() {
    return this->location;
}

void Literal::setLocation(int location) {
    this->location = location;
}

int Literal::getLtorgDump() {
    return this->ltorgDump;
}

void Literal::setLtorgDump(int ltorgDump) {
    this->ltorgDump = ltorgDump;
}
