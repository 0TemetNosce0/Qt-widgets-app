#include "my.h"

#include <string>
#include <fstream>

#include <QString>
#include <QPainter>
#include <QApplication>
#include <QDesktopWidget>
#include <QPropertyAnimation>

//记得要用域名fun::,否则会出现错误
void my::moveToScrCenter(QWidget* object)
{
    object->adjustSize();
    QRect rect = QApplication::desktop()->screenGeometry();
    int scrW = rect.width();
    int scrH = rect.height();
    int x = scrW/2 - object->width()/2 < 0 ? 0 : scrW/2 - object->width()/2;
    int y = scrH/2 - object->height()/2 < 0 ? 0 : (scrH/2 - object->height()/2);
    object->move(x,y);
}

my::Button::Button(const QString& text, QWidget* parent)
    : _text(text)
    , QWidget(parent)
    , _color(Qt::green)
    , radius(-1)
    , _animated(false)
    , _animate_duration(300)
    , _start_size(80,40)
    , _end_size(100,40)
    , _animation(new QPropertyAnimation(this, "size"))
    , white_size(-1)
    , tranparent_background(0)
    , _trans(true)
{
    pen.setColor(Qt::black);
    pen.setWidth(2);
    _font.setFamily("calibri");
    _font.setPixelSize(16);
    _font.setFixedPitch(0);
    adjustMySize();
}

my::Button::~Button()
{
    delete _animation;
}

void my::Button::setSize(int w, int h)
{
    resize(w,h);
    _start_size.setWidth(w);
    _start_size.setHeight(h);
}

void my::Button::setTextPixelSize(int size)
{
    _font.setPixelSize(size);
    adjustMySize();
}

void my::Button::adjustMySize()
{
    int h = QFontMetrics(_font).height() + 4;
    int w = QFontMetrics(_font).width(_text) + 8;
    setMinimumHeight(h);
    setMinimumWidth(w);
}

void my::Button::paintEvent(QPaintEvent *)
{
    if(tranparent_background)
    {
        QPainter pp(this);

        if(!_trans)
        {
            pp.fillRect(0, 0, width() - Animate_Distance, height(), _color);
        }

        pp.setFont(_font);
        pp.setPen(pen);
        pp.drawText(0,0,width()-Animate_Distance,height(),Qt::AlignCenter,_text);

        pp.end();
        return;
    }

#define BRUSH1
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing,1);

    p.setBrush(_color);
#ifdef BRUSH1

    if(white_size > 0)
    {
        QPen pen(Qt::white, white_size);
        p.setPen(pen);

        if(radius < 0)
        {
            p.drawRect(0, 0, width() - Animate_Distance, height());
        }
        else
        {
            p.drawRoundedRect(0, 0, width() - Animate_Distance, height(), radius, radius);
        }
    }
    else
    {
        QPen tpen;
        tpen.setColor(_color);
        tpen.setWidth(0);
        p.setPen(tpen);

        if(radius == -1)
        {
            p.fillRect(0, 0, width() - Animate_Distance, height(), _color);//这种是扁平化风格
        }
        else
        {
            p.drawRoundedRect(0, 0, width() - Animate_Distance, height(), radius, radius);
        }
    }
#else
    if(radius == -1)
    {
        p.drawRect(0, 0, width(), height());
    }
    else
    {
        p.drawRoundedRect(0, 0, width(), height(), radius, radius);
    }
#endif

    p.setFont(_font);
    p.setPen(pen);
    p.drawText(0, 0, width() - Animate_Distance, height(), Qt::AlignCenter, _text);

    p.end();
}

void my::Button::enterEvent(QEvent* )
{
    setCursor(Qt::PointingHandCursor);

    _trans = false;

    if(_animated)
    {
        QPropertyAnimation *p = _animation;
        p->setEasingCurve(QEasingCurve::OutElastic);
        p->setDuration(_animate_duration);
        p->setStartValue(size());
        _start_size = size();
        _end_size.setWidth(size().width() + Animate_Distance);
        _end_size.setHeight(size().height());
        p->setEndValue(_end_size);
        p->start();
    }

    update();
}

void my::Button::leaveEvent(QEvent* )
{
    setCursor(Qt::ArrowCursor);

    _trans = true;

    if(_animated)
    {
        _animation->stop();
        resize(_start_size);
    }

    update();
//    QPropertyAnimation *p=_animation;
//    p->setDuration(_animate_duration);
//    p->setStartValue(_start_size);
//    p->setEndValue(_end_size);

//    p->start();
}

void my::Button::mousePressEvent(QMouseEvent* e)
{
    emit clicked();
    e->accept();
#define WAY1_TO_MOVE_CURSOR
#ifdef WAY1_TO_MOVE_CURSOR
    QCursor::setPos(this->mapToGlobal(QPoint(e->pos().x() + 3, e->pos().y() + 3)));//注意这是全局的座标
#else
    QCursor c(cursor());//这也是全局的座标
    c.setPos(e->pos().x(),e->pos().y()+3);
    setCursor(c);
#endif
}

void my::Button::mouseReleaseEvent(QMouseEvent* e)
{
    QCursor::setPos(this->mapToGlobal(QPoint(e->pos().x() - 3, e->pos().y() - 3)));//注意这是全局的座标
}

void my::Button::mouseMoveEvent(QMouseEvent *e)
{
    e->accept();
}
