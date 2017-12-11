#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, WIDTH, HEIGHT);
    view = new QGraphicsView(scene, this);//384  448
    controller = new gameController(*scene, this);

    view->setBackgroundBrush(QPixmap(":/resource/Resource/background.png"));
    view->setFixedSize(WIDTH + 2, HEIGHT + 2);
    view->setCacheMode(QGraphicsView::CacheBackground);

    setWindowFlags(Qt::FramelessWindowHint);
    setWindowOpacity(0.9);
    setFixedSize(WIDTH + 2, HEIGHT + 2);
    setCentralWidget(view);

    connect(controller, SIGNAL(close()), this, SLOT(close()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
