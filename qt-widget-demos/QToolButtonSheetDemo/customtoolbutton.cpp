#include "customtoolbutton.h"
#include <QPainter>

CustomToolButton::CustomToolButton(QWidget *parent, int iconsize, int btnWidth, int btnHeight, int textsize)
    : QToolButton(parent)
{
    setMouseTracking(true);
    setStyleSheet("border-style:flat;");
    setCheckable(true);

    _bHover = false;
    _bPress = false;
    setArrowType(Qt::NoArrow);

    _mouseHoverPixmap = QPixmap(":/mouse_hover.png");
    _mousePressPixmap = QPixmap(":/mouse_press.png");
    _normalPixmap = QPixmap(":/mouse_disable.png");

    _textDirection = None;

    //计算绘制icon的rect和绘制文字的rect
    if (textsize == 0)
    {
        //不绘制文字，把icon绘制在中间
        _iconrect = QRect((btnWidth - iconsize)/ 2, (btnHeight - iconsize) / 2, iconsize, iconsize);
    }
    else
    {
        //绘制文字，需要考虑文字的高度
        _textrect = QRect(0, btnHeight - textsize, btnWidth, textsize);
        _iconrect = QRect((btnWidth-iconsize)/ 2,(btnHeight - textsize - iconsize) / 2,iconsize, iconsize);
    }
    setIconSize(QSize(iconsize, iconsize));
    setFixedSize(btnWidth, btnHeight);
}

CustomToolButton::~CustomToolButton()
{

}

void CustomToolButton::leaveEvent(QEvent *event)
{
    _bHover = false;
    _bPress = false;
    update();
}

void CustomToolButton::enterEvent(QEvent *event)
{
    _bHover = true;
    update();
}

void  CustomToolButton::mousePressEvent(QMouseEvent *event)
{
    _bHover = false;
    _bPress = true;
    update();
    QToolButton::mousePressEvent(event);
}

void  CustomToolButton::mouseReleaseEvent(QMouseEvent *event)
{
    _bHover = true;
    _bPress = false;
    update();
    QToolButton::mouseReleaseEvent(event);
}

bool CustomToolButton::isHover()
{
    return _bHover;
}

void CustomToolButton::paintEvent(QPaintEvent *event)
{
    QPixmap drawPixmap = QPixmap("");

    if (_bHover)
        drawPixmap = _mouseHoverPixmap;

    else if(_bPress)
        drawPixmap = _mousePressPixmap;

    else
        drawPixmap = _normalPixmap;

    //绘制背景
    QPainter p(this);
    p.drawPixmap(_iconrect, drawPixmap);

    //绘制文字
    if (_textDirection == Down)
    {
        p.setPen(Qt::white);
        p.drawText(_textrect, Qt::AlignCenter, text());
    }
}

void CustomToolButton::setTextDirection(TextDirection textDirection )
{
    _textDirection = textDirection;
}

void CustomToolButton::setMouseHoverPixmap(QPixmap mouseHoverPixmap)
{
    _mouseHoverPixmap = mouseHoverPixmap;
}

void CustomToolButton::setMousePressPixmap(QPixmap mousePressPixmap )
{
    _mousePressPixmap = mousePressPixmap;
}

void CustomToolButton::setNormalPixmap(QPixmap normalPixmap)
{
    _normalPixmap = normalPixmap;
}


