#ifndef MODTABMANAGER_H
#define MODTABMANAGER_H
#include "QList"
#include "QString"
class ModTabManager
{
    QList<QString> modTab;
public:
    ModTabManager();
    void addMod(QString mod);
    QString getAll();
};

#endif // MODTABMANAGER_H
