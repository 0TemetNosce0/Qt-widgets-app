#include "rubber.h"
#include <QMouseEvent>
Rubber::Rubber(QWidget *parent)
{
    setParent(parent);
    this->setBackgroundRole(QPalette::Light);
    this->setAutoFillBackground(true);

    resize(400,360);
    setWindowTitle("Rubber");
    rubberBand = NULL;
}

Rubber::~Rubber()
{

}

//构造函数完成了对窗体尺寸及背景的设置。

void Rubber::mousePressEvent(QMouseEvent *e)
{
    origin = e->pos();
    if(!rubberBand)
        rubberBand = new QRubberBand(QRubberBand::Rectangle,this);
    rubberBand->setGeometry(QRect(origin,QSize()));
    rubberBand->show();
}
//鼠标在窗体中按下时，创建一个QRubberBand 类，QRubberBand::Rectangle 是设置橡皮筋线的类型，这种线的效果是描绘了一个方形的区域，还有一种是QRubberBand::Line，则为一个被直线填满的方形区域，相当于一个阴影的方形区域。QRubberBand 应用最多的函数是 setGeometry(),其作用是设置了橡皮筋线的位置及大小。


//在鼠标按下，并且鼠标发生移动的时候，这时就可以会出橡皮线的区域，鼠标拖动事件函数重载如下 改区域的大小由QRect(origin,e->pos()).normalized()) 来体现， 其中normalized() 函数返回的也是一个QRect的对象，不过该对象的长和宽的值都是大于零时值
void Rubber::mouseMoveEvent(QMouseEvent *e)
{
    if(rubberBand)
        rubberBand->setGeometry(QRect(origin,e->pos()).normalized());
}

//当鼠标松开时，橡皮筋线就可以隐藏了

void Rubber::mouseReleaseEvent(QMouseEvent *e)
{
    if(rubberBand)
        rubberBand->hide();
}

