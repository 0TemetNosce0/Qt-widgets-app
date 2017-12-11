#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myDockTitleBar.h"

#include <QDockWidget>
#include <QToolButton>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMdiSubWindow>
#include <QFrame>
#include <QDebug>

#include <QPainter>
#include <QMouseEvent>
#include <QBitmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QDockWidget *testDock = new QDockWidget(tr("Test Dock"));
    testDock->setFeatures(QDockWidget::DockWidgetClosable | QDockWidget::DockWidgetFloatable
                          | QDockWidget::DockWidgetMovable);
    testDock->setMinimumWidth(200);
    testDock->setStyleSheet(tr("background-color:green;"));

    MyDockTitleBar *titlebar1 = new MyDockTitleBar(testDock);
    testDock->setTitleBarWidget(titlebar1);

    QWidget *testWidget = new QWidget;
    QVBoxLayout *box = new QVBoxLayout;

    QPushButton *okButton = new QPushButton(tr("Ok"));
    okButton->setStyleSheet(tr("background-color:white;"));
    box->addWidget(okButton);
    testWidget->setLayout(box);

    testDock->setWidget(testWidget);

    //////////////////////////////////////////////////////////

    QDockWidget *testDock2 = new QDockWidget(tr("Test Dock2"));
    testDock2->setFeatures(QDockWidget::DockWidgetClosable | QDockWidget::DockWidgetFloatable
                           | QDockWidget::DockWidgetMovable);
    testDock2->setMinimumWidth(200);
    testDock2->setStyleSheet(tr("background-color:orange;"));

    MyDockTitleBar *titlebar2 = new MyDockTitleBar(testDock2);
    testDock2->setTitleBarWidget(titlebar2);

    QWidget *testWidget2 = new QWidget;
    QVBoxLayout *box2 = new QVBoxLayout;

    QPushButton *okButton2 = new QPushButton(tr("Ok"));
    okButton2->setStyleSheet(tr("background-color:white;"));
    box2->addWidget(okButton2);
    testWidget2->setLayout(box2);

    testDock2->setWidget(testWidget2);

    //////////////////////////////////////////////////////////

    this->addDockWidget(Qt::LeftDockWidgetArea, testDock);

    this->setTabPosition(Qt::LeftDockWidgetArea, QTabWidget::West);
    this->tabifyDockWidget(testDock, testDock2);
}

MainWindow::~MainWindow()
{
    delete ui;
}
