#ifndef LOGGERSINGLETON_H
#define LOGGERSINGLETON_H
#include "QString"
#include "QTextEdit"
class LoggerSingleton
{
    static bool instanceFlag;
    static LoggerSingleton* single;
    QTextEdit *_textEdit;
public:
    LoggerSingleton();
    ~LoggerSingleton();
    static LoggerSingleton *getInstance();
    void setTextEdit(QTextEdit *textEdit);
    void writeMessage(const QString &message);
};

#endif // LOGGERSINGLETON_H





