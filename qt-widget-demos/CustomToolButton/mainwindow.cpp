#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "customtoolbutton.h"

#include <QVBoxLayout>
#include <QToolButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    CustomToolButton* pButton = new CustomToolButton(this, 30, 100, 100, 30);
//    QToolButton* pButton = new QToolButton(this);
    pButton->setTextDirection(CustomToolButton::Down);
//    pButton->setIcon(QIcon(":/add.png"));
    pButton->setText("tiananmen");
    pButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    pButton->setPopupMode(QToolButton::InstantPopup);
    QVBoxLayout *pLayout = new QVBoxLayout();

    pLayout->addWidget(pButton);

    ui->centralWidget->setLayout(pLayout);
}

MainWindow::~MainWindow()
{
    delete ui;
}
