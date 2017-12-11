#include "screenshotwindow.h"
#include "ui_screenshotwindow.h"

ScreenShotWindow::ScreenShotWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ScreenShotWindow)
{
    ui->setupUi(this);

    createActions();
    createToolBars();
    fullWidget = new FullScreenWidget();
    //labShotImage = new QLabel(tr("display image"),this);;
    //mainLayout = new QVBoxLayout(this);
    connect(newAct,SIGNAL(triggered()),this,SLOT(screenshot()));
    connect(this,SIGNAL(setPixmap(QPixmap)),fullWidget,SLOT(loadBackgroundPixmap(QPixmap)));
    //connect(fullWidget,SIGNAL(finishPixmap(QPixmap)),labShotImage,SLOT(setPixmap(QPixmap)));

    //mainLayout->addWidget(labShotImage);
    //this->setLayout(mainLayout);
    this->resize(500,300);
}

ScreenShotWindow::~ScreenShotWindow()
{
    delete ui;
}

void ScreenShotWindow::createToolBars()
{
    mainToolBar = new QToolBar("mainToolBar",this);
    mainToolBar->addAction(newAct);
    this->addToolBar(mainToolBar);
}

void ScreenShotWindow::createActions()
{
    newAct = new QAction(QStringLiteral("截屏"),this);
}

void ScreenShotWindow::screenshot()
{
    //hide();
    QPixmap pixmap = fullWidget->getFullScreenPixmap();
    fullWidget->show();

    //发送信号，使用当前的屏幕的图片作背景图片
    emit setPixmap(pixmap);
}

