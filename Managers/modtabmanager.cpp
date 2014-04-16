#include "modtabmanager.h"

ModTabManager::ModTabManager(){
}


void ModTabManager::addMod(QString mod) {
    modTab.push_back(mod);
}

QString ModTabManager::getAll() {
    QString modifications = "";
    foreach (QString mod , modTab) {
        modifications += mod + "\n";
    }
    return modifications;
}

void ModTabManager::ResetState(){
    modTab.clear();
}
