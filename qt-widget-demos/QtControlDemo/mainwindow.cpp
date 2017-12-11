/****************************************
 *
 * http://www.codeforge.cn/article/239048
 *
 ****************************************/

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "customgauge.h"
#include "customcoolbar.h"
#include "custombattery.h"
#include "customindicator.h"
#include "customprogressbar.h"

#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QVBoxLayout *pLayout = new QVBoxLayout();
    pLayout->addWidget(new CustomGauge(this));

    ui->centralWidget->setLayout(pLayout);
}

MainWindow::~MainWindow()
{
    delete ui;
}
