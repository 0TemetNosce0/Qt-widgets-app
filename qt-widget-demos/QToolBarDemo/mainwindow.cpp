#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QVBoxLayout>


/**
 * @brief MainWindow::MainWindow
 * @param parent
 * @ 在QToolBar的最右侧添加按钮
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QToolBar* pToolBar = new QToolBar(this);
    QWidget* spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    // toolBar is a pointer to an existing toolbar
    pToolBar->addWidget(spacer);
    pToolBar->addAction("button");

    QVBoxLayout* pLayout = new QVBoxLayout(this);
    pLayout->addWidget(pToolBar);
    centralWidget()->setLayout(pLayout);
}

MainWindow::~MainWindow()
{
    delete ui;
}
