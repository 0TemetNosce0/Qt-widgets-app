#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    testDateTimeEditEx();
    testDateTimeEdit();

    m_layout = new QVBoxLayout(this);
    centralWidget()->setLayout(m_layout);

    m_layout->addWidget(m_dateTimeEditEx);
    m_layout->addWidget(m_dateTimeEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::testDateTimeEditEx()
{
    m_dateTimeEditEx = new GLDDateTimeEditEx(QDateTime::currentDateTime(), this);
    m_dateTimeEditEx->setCalendarPopup(true);
    m_dateTimeEditEx->setDisplayFormat("yyyy-MM-dd hh:mm:ss");
}

void MainWindow::testDateTimeEdit()
{
    m_dateTimeEdit = new GLDDateTimeEdit(QDateTime::currentDateTime(), this);
    m_dateTimeEdit->setCalendarPopup(true);
    m_dateTimeEdit->setDisplayFormat("yyyy-MM-dd hh:mm:ss");
}
