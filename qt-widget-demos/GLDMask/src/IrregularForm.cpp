#include "irregularform.h"
#include "CustomButton.h"

#include <QLabel>
#include <QDebug>
#include <QPainter>
#include <QPalette>
#include <QMouseEvent>
#include <QApplication>
#include <QDesktopWidget>

IrregularForm::IrregularForm(QWidget *parent)
    : QWidget(parent)
    , m_pCustomBtn(nullptr)
    , m_irregularFormPm("")
{
    setFlagAndAttribute();
}

IrregularForm::IrregularForm(const QString & irregularImgPath, const QString & btnImgPath, QWidget *parent)
    : QWidget(parent)
    , m_pCustomBtn(new CustomButton(btnImgPath, this))
    , m_irregularFormPm("")
{
    setFlagAndAttribute();

    loadPixmap(irregularImgPath);

    connect(m_pCustomBtn, &QPushButton::clicked, this, &IrregularForm::irregularFormClicked);
}

void IrregularForm::setFlagAndAttribute()
{
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_NoSystemBackground);
    setAttribute(Qt::WA_TranslucentBackground);
}

IrregularForm::~IrregularForm()
{

}

QSize IrregularForm::sizeHint() const
{
    if (!m_irregularFormPm.isNull())
    {
        return m_irregularFormPm.size();
    }

    return QWidget::sizeHint();
}

void IrregularForm::loadPixmap(const QString & pixmapPath)
{
    QPixmap tempPixmap;
    tempPixmap.load(pixmapPath);
    setPixmap(tempPixmap);
}

void IrregularForm::setPixmap(const QPixmap & pm)
{
    m_irregularFormPm = pm;
    update();
}

void IrregularForm::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    m_pCustomBtn->move(this->rect().topRight().x() - m_pCustomBtn->width(), this->rect().topRight().y());

    painter.drawPixmap(0, 0, m_irregularFormPm);

    QWidget::paintEvent(event);
}
