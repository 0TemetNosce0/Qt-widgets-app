#include "irregularform.h"
#include "GLDFileUtils.h"

#include <QPainter>
#include <QLabel>
#include <QPalette>

IrregularForm::IrregularForm(QWidget *parent)
    : QWidget(parent)
{
    //���ô����ޱ߿�
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_NoSystemBackground);
    setAttribute(Qt::WA_TranslucentBackground);


    //setAutoFillBackground(true);
    //QPalette palette;
    //palette.setColor(QPalette::Background, QColor(192, 253, 123));
    //setPalette(palette);

    //����ͼ��
    pic.load(exePath() + "/images/Msg/change_skin_text.png");

    resize(pic.size());
}

IrregularForm::~IrregularForm()
{

}

void IrregularForm::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.drawPixmap(0, 0, pic);//����ͼ��

    QWidget::paintEvent(event);
}

void IrregularForm::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);
    emit irregularFormClicked();
}
