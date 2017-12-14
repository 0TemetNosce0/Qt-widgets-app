#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "proxystyle.h"

#include <QDebug>
#include <QListView>
#include <QComboBox>
#include <QCompleter>
#include <QLineEdit>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QComboBox* pCombox = new QComboBox(this);
    pCombox->setEditable(true);
    pCombox->addItem("a");
    pCombox->addItem("a1");
    pCombox->addItem("a2");
    pCombox->addItem("b");
    pCombox->addItem("c");
    QCompleter *pCompleter = new QCompleter(pCombox);
    pCompleter->setModel(pCombox->model());
    pCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    pCombox->setCompleter(pCompleter);

    // 设置样式
    setStyleSheet("QComboBox QAbstractItemView {\
                  border: 2px solid darkgray;\
                  selection-background-color: green;\
                  font: 20px;\
                  font-family: SimSun;\
              }");

    // 设置item选中时无虚线框
    pCombox->setStyle(new CustomProxyStyle);

    QVBoxLayout* pLayout = new QVBoxLayout();

    pLayout->addWidget(pCombox);

    ui->centralWidget->setLayout(pLayout);

    qDebug() << pCombox->lineEdit()->text();
}

MainWindow::~MainWindow()
{
    delete ui;
}
