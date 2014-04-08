#include "loggersingleton.h"

bool LoggerSingleton::instanceFlag = false;
LoggerSingleton* LoggerSingleton::single = NULL;

LoggerSingleton::LoggerSingleton(){
}

LoggerSingleton *LoggerSingleton::getInstance(){
    if(! instanceFlag){
            single = new LoggerSingleton();
            instanceFlag = true;
            return single;
        }else{
            return single;
    }
}

LoggerSingleton::~LoggerSingleton(){
    instanceFlag = false;
}

void LoggerSingleton::setTextEdit(QTextEdit *textEdit){
    _textEdit = textEdit;
}

void LoggerSingleton::writeMessage(const QString &message){
    if (_textEdit) {
           _textEdit->append(message);
       }
}
