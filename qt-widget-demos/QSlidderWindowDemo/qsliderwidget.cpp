#include "qsliderwidget.h"
#include "ui_qsliderwidget.h"
#include "customframe.h"

QSliderWidget::QSliderWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QSliderWidget)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint);
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(on_btn_clicked()));
    ui->pushButton->setVisible(false);
    connect(ui->leftFrame, SIGNAL(signalsMousePosition(int, int)), this, SLOT(slotsMousePosition(int, int)));
    connect(ui->rightFrame, SIGNAL(signalsMousePosition(int, int)), this, SLOT(slotsMousePosition(int, int)));
}

QSliderWidget::~QSliderWidget()
{
    delete ui;
}

void QSliderWidget::on_btn_clicked()
{
    if(ui->leftFrame->isHidden())
    {
        ui->leftFrame->show();
    }
    else
    {
        ui->leftFrame->hide();
    }
}

void QSliderWidget::slotsMousePosition(int ix, int iy)
{
    CustomFrame *pWidow = qobject_cast<CustomFrame *>(sender());

    if(pWidow == ui->rightFrame)
    {
        //这里传入的坐标是当前对象的相对坐标
        int iYTop = (ui->rightFrame->height() - ui->pushButton->height())/2;
        int iYBottom = (ui->rightFrame->height() + ui->pushButton->height())/2;

        if((ix < 10) &&(ix > 0) && (iy > iYTop) && (iy < iYBottom))
        {
            ui->pushButton->show();
        }
        else
        {
            ui->pushButton->hide();
        }
    }
    else
    {
        ui->pushButton->hide();
    }
}
