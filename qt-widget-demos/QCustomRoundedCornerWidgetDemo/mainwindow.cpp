#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "roundedcornerwidget.h"

#include <QVBoxLayout>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_roundedCornerWidget = new RoundedCornerWidget("85", this);
    m_roundedCornerWidget->setSize(QSize(100,100));
    m_roundedCornerWidget->setRadius(50);
    m_roundedCornerWidget->setFontSize(16);
    m_roundedCornerWidget->setShowWidget(true);
    m_roundedCornerWidget->setShowFrame(true);

    QPushButton* btnColor = new QPushButton("turn color",this);
    QPushButton* btnText = new QPushButton("turn Text",this);

    connect(btnColor, SIGNAL(clicked()), this, SLOT(changeColor()));
    connect(btnText, SIGNAL(clicked()), this, SLOT(changeText()));

    QVBoxLayout* pLayout = new QVBoxLayout(this);
    pLayout->addWidget(m_roundedCornerWidget, 0, Qt::AlignCenter);
    pLayout->addWidget(btnColor, 1, Qt::AlignCenter);
    pLayout->addWidget(btnText, 2, Qt::AlignCenter);
    ui->centralWidget->setLayout(pLayout);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeColor()
{
    if(m_roundedCornerWidget->getBackGroundColor() == Qt::blue)
    {
        m_roundedCornerWidget->setBackGroundColor(Qt::red);
        update();
    }
    else
    {
        m_roundedCornerWidget->setBackGroundColor(Qt::blue);
        update();
    }
}

void MainWindow::changeText()
{
    if(m_roundedCornerWidget->getText() == "85")
    {
        m_roundedCornerWidget->setText("63");
        update();
    }
    else
    {
        m_roundedCornerWidget->setText("85");
        update();
    }
}
