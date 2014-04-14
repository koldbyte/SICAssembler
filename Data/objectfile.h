#ifndef OBJECTFILE_H
#define OBJECTFILE_H
#include "QString"
#include "Managers/modtabmanager.h"
#include "Singleton.h"
#include "utils.h"
class ObjectFile
{
    int RECORD_LENGTH;
    QString start;
    QString content;
    QString final;
    void flush();
    QString expand(int number, int size);
public:
    ObjectFile();
    void write(QString what, int address);
    void doWrite(QString what);
    void newLine();
    void writeHeader(int length, QString programName, int startAddress);
    void writeEndOP(int startAddress);
    void flush(int address);
    void close();

    QString getFinal();

};

#endif // OBJECTFILE_H
