#include "littabmanager.h"

LittabManager::LittabManager(){
    ltorgIter = 0;
    //littab = new HashMap<String, Literal>();
}


void LittabManager::addLiteral(QString name, QString value) {
    Utils *utils = &Singleton<Utils>::Instance();

    Literal *l = new Literal();
    l->setLength(utils->getStBytes(value));
    l->setValue(utils->convertOperand(value));
    //littab.insert(value, *l);
    littab.insert(name,*l);
}

int LittabManager::addressOfLiteral(QString name) {
    const Literal l = littab.value(name);
    int loc = l.location;
    return loc;
}

int LittabManager::processLtorg(int locSt) {
    foreach (Literal l, littab) {
        if(l.getLocation() == -1) {
            l.setLocation(locSt);
            locSt += l.getLength();
            l.setLtorgDump(ltorgIter);
        }
    }
    ltorgIter++;
    return locSt;
}

void LittabManager::resetCounter() {
    ltorgIter = 0;
}

QString LittabManager::flushLtorg() {
    QString ret = "";

    foreach (Literal l , littab) {
        if(l.getLtorgDump() == ltorgIter) {
            ret += l.getValue();
        }
    }
    ltorgIter++;
    return ret;
}


