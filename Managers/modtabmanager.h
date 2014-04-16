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
    void ResetState();
};

#endif // MODTABMANAGER_H
