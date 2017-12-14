#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QToolButton>
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QWidget *widget = new QWidget(this);
    QToolButton *buttonNew = new QToolButton(this);
    buttonNew->setText(QStringLiteral("new"));

    QToolButton *buttonOpen = new QToolButton(this);
    buttonOpen->setText(QStringLiteral("apen"));

    QToolButton *buttonOpenFileList = new QToolButton(this);
    buttonOpenFileList->setText(QStringLiteral("file"));

    const int MaxRecentFiles = 10;
    QMenu *menu = new QMenu(this);
    for (int i = 0; i < MaxRecentFiles; ++i)
    {
        QAction *ac = new QAction(this);
        QString text = tr("&%1 %2")
            .arg(i + 1)
            .arg(QStringLiteral("нд╪Ч"));
        ac->setText(text);
        ac->setVisible(true);
        menu->addAction(ac);
    }
    buttonOpenFileList->setMenu(menu);

    QToolButton *buttonSave = new QToolButton(this);
    buttonSave->setText(QStringLiteral("save"));

    QToolButton *buttonOpenSoft = new QToolButton(this);
    buttonOpenSoft->setText(QStringLiteral("open project"));

    QToolButton *buttonOption = new QToolButton(this);
    buttonOption->setText(QStringLiteral("project setting"));

    QHBoxLayout *layout = new QHBoxLayout();
    QToolBar * pToolBar = new QToolBar(widget);
    pToolBar->setStyleSheet("background: #ff0000");
    //pToolBar->setStyleSheet("QToolBar {border-bottom: 2px solid black; border-top: 2px solid black;border-right: 2px solid red}");
//    pToolBar->setStyleSheet("background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\
//    stop: 0 #E1E1E1, stop: 0.4 #FF92BB,\
//      stop: 0.5 #D8D8D8, stop: 1.0 #D3D3D3); ");
    //pToolBar->setStyleSheet("QToolBar{background-image: url(:/Icons/MakeUp32); border: 0px;}");
    pToolBar->addWidget(buttonNew);
    pToolBar->addWidget(buttonOpen);
    pToolBar->addWidget(buttonOpenFileList);
    pToolBar->addWidget(buttonSave);
    pToolBar->addWidget(buttonOpenSoft);
    pToolBar->addWidget(buttonOption);
    //layout->addWidget(buttonNew);
    //layout->addWidget(buttonOpen);
    //layout->addWidget(buttonOpenFileList);
    //layout->addWidget(buttonSave);
    //layout->addStretch();
    //layout->addWidget(buttonOpenSoft);
    //layout->addWidget(buttonOption);
    layout->addWidget(pToolBar);
    widget->setLayout(layout);

    setCentralWidget(widget);
}

MainWindow::~MainWindow()
{
    delete ui;
}
