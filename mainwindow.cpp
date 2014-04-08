#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    LoggerSingleton *logger=LoggerSingleton::getInstance();
    logger->setTextEdit(ui->consoleText);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered(){
    QString fileName = QFileDialog::getOpenFileName(this,
             tr("Open Source Code"), "",
             tr("Source Code (*.sic);Text File(*.txt);;All Files (*)"));
    if (fileName.isEmpty())
             return;
         else {
             QFile file(fileName);

             if (!file.open(QIODevice::ReadOnly)) {
                 QMessageBox::information(this, tr("Unable to open file"),
                     file.errorString());
                 return;
             }

             QTextStream stream(&file);
             ui->SourceCodeTextEdit->clear();
             QString in;
             in = stream.readAll();
             //stream >> in;
             ui->SourceCodeTextEdit->setPlainText(in);
        }
}

void MainWindow::on_actionSave_to_File_triggered(){
    QString fileName = QFileDialog::getSaveFileName(this,
             tr("Save Source Code"), "",
             tr("Source Code (*.sic);Text File(*.txt);;All Files (*)"));
    if (fileName.isEmpty())
             return;
         else {
             QFile file(fileName);
             if (!file.open(QIODevice::WriteOnly)) {
                 QMessageBox::information(this, tr("Unable to Save file"),
                     file.errorString());
                 return;
             }
             QTextStream stream(&file);
             stream << ui->SourceCodeTextEdit->toPlainText();
        }
}

void MainWindow::on_actionSave_Output_triggered(){
    QString fileName = QFileDialog::getSaveFileName(this,
             tr("Save Object Code"), "",
             tr("Source Code (*.obj);Text File(*.txt);;All Files (*)"));
    if (fileName.isEmpty())
             return;
         else {
             QFile file(fileName);
             if (!file.open(QIODevice::WriteOnly)) {
                 QMessageBox::information(this, tr("Unable to Save file"),
                     file.errorString());
                 return;
             }
             QTextStream stream(&file);
             stream << ui->ObjectCodeText->toPlainText();
        }
}

void MainWindow::on_actionExit_triggered()
{
    this->close();
    //exit(0);
}

void MainWindow::on_actionConvert_Now_triggered()
{
    ui->ObjectCodeText->clear();
    //QList<QString> code;
    Assembler *assembler = &Singleton<Assembler>::Instance();
    assembler->Assemble(ui->SourceCodeTextEdit->toPlainText());
    /*code = assembler->getCode();
    QString cc = "";
    foreach(QString x , code){
        cc.append(x);
        cc.append("\r\n");
    }*/
    QString cc = assembler->prepareHeaderCode();
    ui->ObjectCodeText->clear();
    ui->ObjectCodeText->setPlainText(cc);
}

void MainWindow::writeToConsole(QString s){
    ui->consoleText->append(s);
    ui->consoleText->append("\n");
}
