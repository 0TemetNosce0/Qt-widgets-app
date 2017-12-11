#include "irregularform.h"
#include "ui_irregularform.h"

#include <QPainter>

IrregularForm::IrregularForm(QWidget *parent)
    : QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);//设置窗体无边框

    setAttribute(Qt::WA_TranslucentBackground);//设置背景透明

    pic.load(":/res/images/change_skin_text.png");//加载图像

    resize(pic.size());
}

IrregularForm::~IrregularForm()
{

}

void IrregularForm::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);

    painter.drawPixmap(0, 0, pic);//绘制图像
}
