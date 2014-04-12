#ifndef REGISTERMANAGER_H
#define REGISTERMANAGER_H
#include "QMap"
#include "Singleton.h"
class RegisterManager
{
    QMap<QString,int> m_registers;
    QMap<QString,int> ::iterator m_it;
public:
    RegisterManager();

    int getRegisterCount();
    int getAddress(QString label);
    int getAddress(int i);

    QString getRegister(int address);
    QString getRegister(int i,int c);

    void insertRegister(QString,int);
};

#endif // REGISTERMANAGER_H
