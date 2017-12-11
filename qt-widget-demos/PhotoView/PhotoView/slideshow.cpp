#include "slideshow.h"
#include "ui_slideshow.h"
#include "mainwindow.h"

SlideShow::SlideShow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SlideShow)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);

    MainWindow *w = (MainWindow *)this->parentWidget();
    PhotoMap = w->GetAllFileInfo();

    PhotoIndex = 0;
    image.load(PhotoMap.value(PhotoIndex).absoluteFilePath());

    timer = new QTimer(this);
    timer->setInterval(1000);
    connect(timer,SIGNAL(timeout()),this,SLOT(SwitchPhoto()));
    timer->start();

    this->showFullScreen();
}

SlideShow::~SlideShow()
{
    delete ui;
}


void SlideShow::ZoomFit()
{
    qreal pw = image.width();
    qreal ph = image.height();
    qreal ww = ui->Photo->width();
    qreal wh = ui->Photo->height();
    QImage image1;

    if(pw <= ww && ph <= wh)
    {
        image1 = image;
    }
    else
    {
        image1 = image.scaled(ui->Photo->width(),ui->Photo->height(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
    }
    ui->Photo->setPixmap(QPixmap::fromImage(image1));
}

void SlideShow::resizeEvent(QResizeEvent *)
{
    ZoomFit();
}

void SlideShow::SwitchPhoto()
{
    if(++PhotoIndex >= PhotoMap.count())
    {
        PhotoIndex = 0;
    }

    image.load(PhotoMap.value(PhotoIndex).absoluteFilePath());
    ZoomFit();
}



void SlideShow::keyPressEvent(QKeyEvent* event)
{
    if(event->key() == Qt::Key_Escape)
    {
        emit hideMe();
    }
}
