#include "CustomButton.h"
#include <QPainter>


CustomButton::CustomButton(QWidget *parent)
    : QPushButton(parent)
    , m_pixmap("")
{

}

CustomButton::CustomButton(const QString &iconPath, QWidget* parent)
    : QPushButton(parent)
    , m_pixmap("")
{
    QPixmap btnPixmap;
    btnPixmap.load(iconPath);
    setPixmap(btnPixmap);
}

void CustomButton::setPixmap(const QPixmap& pm)
{
    m_pixmap = pm;
    update();
}

QSize CustomButton::sizeHint() const
{
    if (!m_pixmap.isNull())
    {
        return m_pixmap.size();
    }

    return QPushButton::sizeHint();
}

void CustomButton::paintEvent(QPaintEvent* e)
{
    Q_UNUSED(e);
    QPainter p(this);
    p.drawPixmap(0, 0, m_pixmap);
}