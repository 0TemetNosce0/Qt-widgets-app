#include "rubber.h"
#include "ui_rubber.h"

#include <QMouseEvent>

Rubber::Rubber(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Rubber)
{
    ui->setupUi(this);

    this->setBackgroundRole(QPalette::Light);
    this->setAutoFillBackground(true);
    resize(400,360);
    setWindowTitle("Rubber");
    rubberBand = NULL;
}

Rubber::~Rubber()
{
    delete ui;
}

void Rubber::mousePressEvent(QMouseEvent *e)
{
    origin = e->pos();

    if(!rubberBand)
    {
        rubberBand = new QRubberBand(QRubberBand::Rectangle, this);
    }

    rubberBand->setGeometry(QRect(origin,QSize()));
    rubberBand->show();
}

void Rubber::mouseMoveEvent(QMouseEvent *e)
{
    if(rubberBand)
    {
        rubberBand->setGeometry(QRect(origin,e->pos()).normalized());
    }
}

void Rubber::mouseReleaseEvent(QMouseEvent *e)
{
    if(rubberBand)
    {
        rubberBand->hide();
    }
}
