#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QPlainTextEdit"
#include "QTextEdit"
#include "Gui/codeeditor.h"
#include "QFileDialog"
#include "QMessageBox"
#include "QTextStream"
#include "assembler.h"
#include "Gui/loggersingleton.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void writeToConsole(QString s);
    void updateSymbolsTab();
    void updateInsTab();
    void updateLiteralTab();
    void clearOutput();

private slots:
    void on_actionOpen_triggered();

    void on_actionSave_to_File_triggered();

    void on_actionSave_Output_triggered();

    void on_actionExit_triggered();

    void on_actionConvert_Now_triggered();

    void on_actionClear_Ouputs_triggered();

    void on_actionSave_Output_2_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

