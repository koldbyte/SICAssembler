#include "objectfile.h"

ObjectFile::ObjectFile(){
    RECORD_LENGTH = 60;
    content = "";
    final = "";
}

void ObjectFile::write(QString what, int address){
    if(content.length() == 0) {
        start = "T" + expand(address, 6);
    }
    if(content.length() + what.length() > RECORD_LENGTH) {
        flush(address);
    }
    content.append(what);
}

void ObjectFile::doWrite(QString what){
    final += what;
}

void ObjectFile::newLine() {
    final += "\n";
}

void ObjectFile::writeHeader(int length, QString programName, int startAddress) {
    doWrite("H" + programName + " " + expand(startAddress, 6) + expand(length, 6));
    newLine();
}

void ObjectFile::writeEndOP(int startAddress) {
    if(content.length() > 0) {
        flush();
    }
    ModTabManager *mtMan = &Singleton<ModTabManager>::Instance();
    doWrite(mtMan->getAll());
    doWrite("E" + expand(startAddress, 6));
    newLine();
}

void ObjectFile::flush() {
    flush(-1);
}

void ObjectFile::flush(int address) {
    if(content.length() == 0)
        return;

    start += expand(content.length()/2, 2);
    doWrite(start + content);
    newLine();
    //content.setLength(0);
    content = "";
    start = "T" + expand(address, 6);
}

void ObjectFile::close() {
    return;
}

QString ObjectFile::expand(int number, int size) {
    Utils *utils = &Singleton<Utils>::Instance();
    return utils->expand(number, size);
}

QString ObjectFile::getFinal(){
    return this->final;
}
