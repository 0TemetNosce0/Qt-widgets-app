#include "mainwindow.h"
#include "form.h"

#include <QDockWidget>
#include <QTextEdit>
#include <QCalendarWidget>
#include <QListWidget>
#include <QMenu>
#include <QMenuBar>
#include <QAction>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
{
    createmenu();

    createdock1();
    createdock2();
    createdock3();

    //创建QTextEdit对象
    m_pTextEdit = new QTextEdit(this);
    setCentralWidget(m_pTextEdit);

    //主窗口中添加dock
    addDockWidget(Qt::LeftDockWidgetArea, m_pDockWidget1);
    addDockWidget(Qt::LeftDockWidgetArea, m_pDockWidget2);
    addDockWidget(Qt::LeftDockWidgetArea, m_pDockWidget3);

    m_pVMenu->addAction(m_pDockWidget1->toggleViewAction());
    m_pVMenu->addAction(m_pDockWidget2->toggleViewAction());
    m_pVMenu->addAction(m_pDockWidget3->toggleViewAction());

    setWindowTitle("www.hnmade.com");
}

void MainWindow::createmenu()
{
    m_pFMenu = menuBar()->addMenu("&File");
    m_pExit = new QAction(tr("&Exit"), this);
    m_pExit->setShortcuts(QKeySequence::Quit);
    connect(m_pExit, SIGNAL(triggered()), this, SLOT(close()));
    m_pFMenu->addAction(m_pExit);
    m_pVMenu = menuBar()->addMenu("&View");
}

void MainWindow::createdock1()
{
    //创建QDockWidget对象
    m_pDockWidget1 = new QDockWidget(this);
    m_pDockWidget1->setWindowTitle("dock date");
    //设置可停靠的区域
    m_pDockWidget1->setAllowedAreas(Qt::AllDockWidgetAreas);
    //设置m_pDockWidget1内的部件
    m_pCale = new QCalendarWidget(m_pDockWidget1);
    m_pCale->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_pCale->setGridVisible(true);
    m_pDockWidget1->setWidget(m_pCale);
}

void MainWindow::createdock2()
{
    m_pDockWidget2 = new QDockWidget(this);
    m_pDockWidget2->setWindowTitle("dock type");
    m_pDockWidget2->setAllowedAreas(Qt::AllDockWidgetAreas);
    m_pForm = new Form(m_pDockWidget2);
    m_pDockWidget2->setWidget(m_pForm);
}

void MainWindow::createdock3()
{
    m_pDockWidget3 = new QDockWidget(this);
    m_pDockWidget3->setWindowTitle("dock log");
    m_pDockWidget3->setAllowedAreas(Qt::AllDockWidgetAreas);
    m_pList = new QListWidget(m_pDockWidget3);
    m_pList->addItem("start the program succ");
    m_pList->addItem("open the file succ");
    m_pList->addItem("undo the file succ");
    m_pList->addItem("open the file succ");
    m_pList->addItem("save the file succ");
    m_pDockWidget3->setWidget(m_pList);
}

MainWindow::~MainWindow()
{

}
