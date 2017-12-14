#include "customtoolbutton.h"
#include <QPainter>

CustomToolButton::CustomToolButton(QWidget *parent, int iconsize, int btnWidth, int btnHeight, int textsize)
    : QToolButton(parent)
{
    setMouseTracking(true);
    setStyleSheet("border-style:flat;");
    setCheckable(true);

    m_bHover = false;
    m_bPress = false;
    setArrowType(Qt::NoArrow);

    m_mouseHoverPixmap = QPixmap(":/anchor.png");
    m_mousePressPixmap = QPixmap(":/accept.png");
    m_normalPixmap = QPixmap(":/application.png");

    m_textDirection = None;

    //�������icon��rect�ͻ������ֵ�rect
    if (textsize == 0)
    {
        //���������֣���icon�������м�
        m_iconrect = QRect((btnWidth - iconsize)/ 2, (btnHeight - iconsize) / 2, iconsize, iconsize);
    }
    else
    {
        //�������֣���Ҫ�������ֵĸ߶�
        m_textrect = QRect(0, btnHeight - textsize, btnWidth, textsize);
        m_iconrect = QRect((btnWidth-iconsize)/ 2,(btnHeight - textsize - iconsize) / 2,iconsize, iconsize);
    }
    setIconSize(QSize(iconsize, iconsize));
    setFixedSize(btnWidth, btnHeight);
}

CustomToolButton::~CustomToolButton()
{

}

void CustomToolButton::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);

    m_bHover = false;
    m_bPress = false;
    update();
}

void CustomToolButton::enterEvent(QEvent *event)
{
    Q_UNUSED(event);

    m_bHover = true;
    update();
}

void  CustomToolButton::mousePressEvent(QMouseEvent *event)
{
    m_bHover = false;
    m_bPress = true;
    update();
    QToolButton::mousePressEvent(event);
}

void  CustomToolButton::mouseReleaseEvent(QMouseEvent *event)
{
    m_bHover = true;
    m_bPress = false;
    update();
    QToolButton::mouseReleaseEvent(event);
}

bool CustomToolButton::isHover()
{
    return m_bHover;
}

void CustomToolButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPixmap drawPixmap;

    if (m_bHover)
    {
        drawPixmap = m_mouseHoverPixmap;
    }
    else if(m_bPress)
    {
        drawPixmap = m_mousePressPixmap;
    }
    else
    {
        drawPixmap = m_normalPixmap;
    }

    //���Ʊ���
    QPainter p(this);
    p.drawPixmap(m_iconrect, drawPixmap);

    //��������
    if (m_textDirection == Down)
    {
        p.setPen(Qt::red);
        p.drawText(m_textrect, Qt::AlignCenter, text());
    }
    else if(m_textDirection == Right)
    {
        p.setPen(Qt::black);
        p.drawText(m_textrect, Qt::AlignLeft, text());
    }
}

void CustomToolButton::setTextDirection(TextDirection textDirection )
{
    m_textDirection = textDirection;
}

void CustomToolButton::setMouseHoverPixmap(QPixmap mouseHoverPixmap)
{
    m_mouseHoverPixmap = mouseHoverPixmap;
}

void CustomToolButton::setMousePressPixmap(QPixmap mousePressPixmap )
{
    m_mousePressPixmap = mousePressPixmap;
}

void CustomToolButton::setNormalPixmap(QPixmap normalPixmap)
{
    m_normalPixmap = normalPixmap;
}


