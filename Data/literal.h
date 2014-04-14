#ifndef LITERAL_H
#define LITERAL_H
#include "QString"
#include "Singleton.h"
#include "utils.h"
class Literal
{
    int value;
    int length;
    int ltorgDump;
public:
    Literal();
    int location;

    QString getValue();
    void setValue(int value);
    int getLength();
    void setLength(int length);
    int getLocation();
    void setLocation(int location);
    int getLtorgDump();
    void setLtorgDump(int ltorgDump);

};

#endif // LITERAL_H
