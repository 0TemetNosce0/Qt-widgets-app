#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QLabel>
#include <QSpinBox>
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowIcon(QIcon(":/360buy.ico"));

    QLabel *label =  new QLabel(QStringLiteral("±êÇ©"));
    gld::GLDDoubleSpinBoxEx *pBox = new gld::GLDDoubleSpinBoxEx(this);
    pBox->setHasBorder(true);

    QHBoxLayout *pLayout = new QHBoxLayout(this);
    pLayout->addWidget(label);
    pLayout->addWidget(pBox);

    ui->centralWidget->setLayout(pLayout);

}

MainWindow::~MainWindow()
{
    delete ui;
}
