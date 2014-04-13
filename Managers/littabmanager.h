#ifndef LITTABMANAGER_H
#define LITTABMANAGER_H
#include "QMap"
#include "QString"
#include "Data/literal.h"
#include "utils.h"
#include "Singleton.h"

class LittabManager
{
    int ltorgIter;
    QMap<QString, Literal> littab;
public:
    LittabManager();
    void addLiteral(QString name, QString value);
    int addressOfLiteral(QString name);
    int processLtorg(int locSt);
    void resetCounter();
    QString flushLtorg();
    int convertedOperand(QString s);
    int getStBytes(QString s);


};

#endif // LITTABMANAGER_H
