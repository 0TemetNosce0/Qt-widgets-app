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
    newAct = new QAction(QStringLiteral("����"),this);
}

void ScreenShotWindow::screenshot()
{
    //hide();
    QPixmap pixmap = fullWidget->getFullScreenPixmap();
    fullWidget->show();

    //�����źţ�ʹ�õ�ǰ����Ļ��ͼƬ������ͼƬ
    emit setPixmap(pixmap);
}

