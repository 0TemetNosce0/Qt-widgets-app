#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "textedit.h"

#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    TextEdit* editor = new TextEdit();

    QVBoxLayout* pLayout = new QVBoxLayout(this);

    pLayout->addWidget(editor);

    ui->centralWidget->setLayout(pLayout);
}

MainWindow::~MainWindow()
{
    delete ui;
}
