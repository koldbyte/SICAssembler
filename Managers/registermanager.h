#ifndef REGISTERMANAGER_H
#define REGISTERMANAGER_H
#include "QMap"

class RegisterManager
{
    QMap<QString,int> m_registers;
public:
    RegisterManager();

    int getRegisterCount();
    int getAddress(QString label);
    int getAddress(int i);

    QString getLabel(int address);
    QString getRegister(int i);

    insertRegister(QString,int);
};

#endif // REGISTERMANAGER_H
