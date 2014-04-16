#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    LoggerSingleton *logger=LoggerSingleton::getInstance();
    logger->setTextEdit(ui->consoleText);

    //Initialize Symbols Table Widget
    ui->symbols_table->setColumnCount(2);
    QStringList m_TableHeader;
    m_TableHeader << "Label" << "Address";
    ui->symbols_table->setHorizontalHeaderLabels(m_TableHeader);
    ui->symbols_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->symbols_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->symbols_table->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->symbols_table->setRowCount(0);

    //Initialize Instruction Table Widget
    //label operator operand loc object code
    ui->ins_table->setColumnCount(5);
    QStringList m_TableHeader2;
    m_TableHeader2 << "Label" << "Operator" << "Operand" << "Loc" << "Object Code";
    ui->ins_table->setHorizontalHeaderLabels(m_TableHeader2);
    ui->ins_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->ins_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->ins_table->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->ins_table->setRowCount(0);

    //Initialize Literal Table Widget
    //string  value length location
    ui->lit_table->setColumnCount(4);
    QStringList m_TableHeader3;
    m_TableHeader3 << "Label" << "Value" << "Length" << "Location";
    ui->lit_table->setHorizontalHeaderLabels(m_TableHeader3);
    ui->lit_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->lit_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->lit_table->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->lit_table->setRowCount(0);

    ui->SourceCodeTextEdit->setFocus();
    //testing only
    //OptabManager *opMan = &Singleton<OptabManager>::Instance();
    //qDebug() << qPrintable(QString::number(opMan->getShiftedOpcode("STL")));
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
    clearOutput();
    ui->ObjectCodeText->clear();
    Assembler *assembler = &Singleton<Assembler>::Instance();
    QString source = ui->SourceCodeTextEdit->toPlainText();
    source.replace('\t',' ');
    ui->SourceCodeTextEdit->setPlainText(source);
    assembler->Assemble(source);

    QString cc = assembler->getFinalCode();
    cc = cc.toUpper();
    ui->ObjectCodeText->clear();
    ui->ObjectCodeText->setPlainText("");
    ui->ObjectCodeText->setPlainText(cc);

    //update Symbols Table
    this->updateSymbolsTab();

    //update Ins Table
    this->updateInsTab();

    //update Lit Table
    this->updateLiteralTab();
}

void MainWindow::writeToConsole(QString s){
    ui->consoleText->append(s);
    ui->consoleText->append("\n");
}

void MainWindow::updateSymbolsTab(){
    while (ui->symbols_table->rowCount() > 0){
        ui->symbols_table->removeRow(0);
    }
    ui->symbols_table->setRowCount(0);

    SymtabManager *symMan = &Singleton<SymtabManager>::Instance();
    QVector<Symbol> sym = symMan->getAllSymbols();
    QVector<Symbol> ::iterator it;
    ui->symbols_table->setRowCount(sym.size());
    int i=0;
    for(it=sym.begin()+7;it!=sym.end();it++){
        ui->symbols_table->setItem(i,0, new QTableWidgetItem(it->getLabel()));
        ui->symbols_table->setItem(i,1, new QTableWidgetItem(QString::number(it->getAddress(),16).toUpper()));
        i++;
    }
    ui->symbols_table->setRowCount(i);

}

void MainWindow::updateInsTab(){
    while (ui->ins_table->rowCount() > 0){
            ui->ins_table->removeRow(0);
        }
        ui->ins_table->setRowCount(0);

        Assembler *assembler = &Singleton<Assembler>::Instance();
        QList<Instruction> ins = assembler->getAllInstructions();
        QList<Instruction> ::iterator it;
        ui->ins_table->setRowCount(ins.size());
        int i=0;
        for(it=ins.begin();it!=ins.end();it++){
            //label operator operand loc object code
            if(it->getObjectCode()!=""){
                ui->ins_table->setItem(i,0, new QTableWidgetItem(it->getLabel()));
                ui->ins_table->setItem(i,1, new QTableWidgetItem(it->getOperator()));
                ui->ins_table->setItem(i,2, new QTableWidgetItem(it->getOperand()));
                ui->ins_table->setItem(i,3, new QTableWidgetItem(QString::number(it->getloc(),16).toUpper()));
                ui->ins_table->setItem(i,4, new QTableWidgetItem(it->getObjectCode().toUpper()));
                i++;
            }
        }
        ui->ins_table->setRowCount(i);
}

void MainWindow::updateLiteralTab(){
    while (ui->lit_table->rowCount() > 0){
            ui->lit_table->removeRow(0);
        }
        ui->lit_table->setRowCount(0);

        LittabManager *ltMan = &Singleton<LittabManager>::Instance();
        QMap<QString, Literal> lit = ltMan->getLittab();
        QMap<QString, Literal> ::iterator it;
        ui->lit_table->setRowCount(lit.size());
        qDebug() << "Literal Table size is" << qPrintable(QString::number(lit.size()));
        int i=0;
        for(it=lit.begin();it!=lit.end();it++){
            //string  value length location
                ui->lit_table->setItem(i,0, new QTableWidgetItem(it.key()));
                ui->lit_table->setItem(i,1, new QTableWidgetItem(it->getValue()));
                ui->lit_table->setItem(i,2, new QTableWidgetItem(QString::number(it->getLength())));
                ui->lit_table->setItem(i,3, new QTableWidgetItem(QString::number(it->getLocation())));
                i++;

        }
        ui->lit_table->setRowCount(i);
}

void MainWindow::clearOutput(){
    ui->ObjectCodeText->clear();
    ui->ObjectCodeText->setPlainText("");

    while (ui->symbols_table->rowCount() > 0){
        ui->symbols_table->removeRow(0);
    }
    ui->symbols_table->setRowCount(0);

    while (ui->ins_table->rowCount() > 0){
            ui->ins_table->removeRow(0);
    }
    ui->ins_table->setRowCount(0);

    while (ui->lit_table->rowCount() > 0){
            ui->lit_table->removeRow(0);
    }
    ui->lit_table->setRowCount(0);

    //reset instance of manager classes..
    SymtabManager *symMan = &Singleton<SymtabManager>::Instance();
    Assembler *assembler = &Singleton<Assembler>::Instance();
    ModTabManager *modMan = &Singleton<ModTabManager>::Instance();

    symMan->ResetState();
    assembler->ResetState();
    modMan->ResetState();

}


void MainWindow::on_actionClear_Ouputs_triggered(){
    this->clearOutput();
}

void MainWindow::on_actionSave_Output_2_triggered(){
    Assembler *assembler = &Singleton<Assembler>::Instance();
    QList<Instruction> ins = assembler->getAllInstructions();
    QList<Instruction> ::iterator it;
    QString out = "";
    out += "LOCCTR      LABEL       OPERATOR        OPERAND         OBJECTCODE\n";
    //12 12 16 16 10
    out += "--------------------------------------------------------------------\n";
    int i=0;
    for(it=ins.begin();it!=ins.end();it++){
        //label operator operand loc object code
        QString line = "";
        if(it->getObjectCode()!=""){
            line +=it->getLabel().leftJustified(12,' ');
            line +=it->getOperator().leftJustified(12,' ');
            line +=it->getOperand().leftJustified(16,' ');
            line +=QString::number(it->getloc(),16).toUpper().leftJustified(16,' ');
            line +=it->getObjectCode().toUpper().leftJustified(10,' ');
            out += line + "\n";
            i++;
        }
    }
    QString fileName = QFileDialog::getSaveFileName(this,
             tr("Save Output"), "",
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
             stream << out;
        }
}
