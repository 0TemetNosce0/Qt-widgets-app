#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Untitled ---notepad");
    connect(ui->action_N,SIGNAL(triggered()),this,SLOT(newFileSlot()));
    connect(ui->action2_O,SIGNAL(triggered()),this,SLOT(openFileSlot()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newFileSlot(){
    if(ui->textEdit->document()->isModified())
    {
        qDebug()<<"have modified";
    }
    else
    {
        //qDebug()<<"unmodified";
        ui->textEdit->clear();
        this->setWindowTitle("Untitled.txt");
    }
}


void MainWindow::openFileSlot(){

    QString fileName = QFileDialog::getOpenFileName(this,"Open File",QDir::currentPath());

    if(fileName.isEmpty())
    {
        QMessageBox::information(this,"error message","please select a file");
        return;
    }

    QFile *file = new QFile();
    file->setFileName(fileName);

    if(file->open(QIODevice::ReadOnly))
    {
        QTextStream in(file);
        ui->textEdit->setText(in.readAll());
        file->close();
        delete file;
    }
    else
    {
        QMessageBox::information(this,"Error Message","Open File Fail");
        return;
    }
}


void MainWindow::saveFileSlot()
{
    QString fileName = QFileDialog::getSaveFileName(this,"Open File",QDir::currentPath());

    if(fileName.isEmpty())
    {
        QMessageBox::information(this,"Error Message","please select a file");
        return;
    }

    QFile *file = new QFile();
    file->setFileName(fileName);

    if(file->open(QIODevice::WriteOnly))
    {
        QTextStream out(file);
        out<<ui->textEdit->toPlainText();
        file->close();
        this->setWindowTitle(fileName + "notepad");
        delete file;
    }
    else
    {
        QMessageBox::information(this,"Error Message","Save File Fail");
        return;
    }
}
