#include "irregularform.h"
#include "ui_irregularform.h"

#include <QPainter>

IrregularForm::IrregularForm(QWidget *parent)
    : QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);//���ô����ޱ߿�

    setAttribute(Qt::WA_TranslucentBackground);//���ñ���͸��

    pic.load(":/res/images/change_skin_text.png");//����ͼ��

    resize(pic.size());
}

IrregularForm::~IrregularForm()
{

}

void IrregularForm::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);

    painter.drawPixmap(0, 0, pic);//����ͼ��
}
