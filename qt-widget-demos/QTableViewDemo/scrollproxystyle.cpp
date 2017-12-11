#include "scrollproxystyle.h"
#include <QStyleOptionSlider>
#include <QPainter>

ScrollProxyStyle::ScrollProxyStyle()
{

}

ScrollProxyStyle::~ScrollProxyStyle()
{

}

void ScrollProxyStyle::drawComplexControl(QStyle::ComplexControl control, const QStyleOptionComplex *option,
                                     QPainter *painter, const QWidget *widget) const
{
    switch (control)
    {
    case CC_ScrollBar:
        drawScrollbar(control, option, painter, widget);
        return;
    default:
        break;
    }

    QProxyStyle::drawComplexControl(control, option, painter, widget);
}

void ScrollProxyStyle::drawScrollbar(QStyle::ComplexControl control, const QStyleOptionComplex *option,
                                QPainter *painter, const QWidget *widget) const
{
    //QQ中滚动条的效果是:如果不在滚动条上,默认上下箭头不显示,AddPage, SubPage也不显示
    //如果在滚动条上,如果不在箭头所在的区域,则显示normal,否则显示hot,按下显示down,这里按这个标准实现
    const QStyleOptionSlider *scrollbar = qstyleoption_cast<const QStyleOptionSlider *>(option);

    if(!scrollbar)
    {
        return;
    }

    bool maxedOut = (scrollbar->maximum == scrollbar->minimum);

//    if(maxedOut)
//    {
//        return;
//    }

    State flags = option->state;

    if (widget && widget->testAttribute(Qt::WA_UnderMouse) && widget->isActiveWindow())
    {
        flags |= State_MouseOver;
    }

    if (maxedOut)
    {
        flags &= ~State_Enabled;
    }

    painter->save();

    painter->setRenderHint(QPainter::Antialiasing);
    const bool pressed = flags & State_Sunken;
    const bool mouseOver = flags & State_MouseOver;
    const bool isHorz = flags & State_Horizontal;


    QColor bkFillColor    = Qt::white;
    QColor bkSliderNormal = Qt::lightGray;
    QColor bkSliderHover  = Qt::gray;
    QColor bkSliderPress  = Qt::darkGray;


    QRect drawRect;
    //清除所有子控件背景,上下（左右）箭头可能和沟槽的背景不一样
    drawRect = subControlRect(CC_ScrollBar, option, SC_ScrollBarAddLine, widget);
    painter->fillRect(drawRect, bkFillColor);
    drawRect = subControlRect(CC_ScrollBar, option, SC_ScrollBarSubLine, widget);
    painter->fillRect(drawRect, bkFillColor);

    //沟槽的颜色
    drawRect = subControlRect(CC_ScrollBar, option, SC_ScrollBarGroove, widget);
    painter->fillRect(drawRect, Qt::green);

    //在mouse over状态下,才绘制上下左右箭头
    //scrollbar->activeSubControls用于指定当前鼠标所在的子控件
    const QStyle::SubControls sc = scrollbar->activeSubControls;

    const SubControls sub = option->subControls;

    if(!mouseOver)
    {
        //只绘制Slider，其余清除
        drawRect = subControlRect(CC_ScrollBar, option, SC_ScrollBarSlider, widget);
        QPainterPath painterPath;
        painterPath.addRoundedRect(drawRect.left(), drawRect.top(), drawRect.width(), drawRect.height(), 4, 4);
        painter->fillPath(painterPath, bkSliderNormal);
    }
    else
    {
        //合并绘制AddPage SubPage
        drawRect = subControlRect(CC_ScrollBar, option, SC_ScrollBarGroove, widget);
        painter->fillRect(drawRect, QColor(192, 192, 192, 127));

        //画加号,应该区分水平和垂直
        if (sub & SC_ScrollBarAddLine)
        {
            drawRect = subControlRect(CC_ScrollBar, option, SC_ScrollBarAddLine, widget);
            QPixmap pixmap;

            if(isHorz)
            {
                if(pressed)
                {
                    pixmap.load(":/qss/icons/scrollleftarrow.png");
                }
                else if(sc & SC_ScrollBarAddLine)
                {
                    pixmap.load(":/qss/icons/scrollrightarrow.png");
                }
                else
                {
                    pixmap.load(":/qss/icons/scrollrightarrow.png");
                }
            }
            else
            {
                if(pressed)
                {
                    pixmap.load(":/qss/icons/scrolldownarrow.png");
                }
                else if(sc & SC_ScrollBarAddLine)
                {
                    pixmap.load(":/qss/icons/scrolluparrow.png");
                }
                else
                {
                    pixmap.load(":/qss/icons/scrolluparrow.png");
                }
            }

            painter->drawPixmap(drawRect, pixmap);
        }

        if (sub & SC_ScrollBarSubLine)
        {
            drawRect = subControlRect(CC_ScrollBar, option, SC_ScrollBarSubLine, widget);
            QPixmap pixmap;

            if(isHorz)
            {
                if(pressed)
                {
                    pixmap.load(":/qss/icons/scrollleftarrow.png");
                }
                else if(sc & SC_ScrollBarSubLine)
                {
                    pixmap.load(":/qss/icons/scrollrightarrow.png");
                }
                else
                {
                    pixmap.load(":/qss/icons/scrollrightarrow.png");
                }
            }
            else
            {
                if(pressed)
                {
                    pixmap.load(":/qss/icons/scrolldownarrow.png");
                }
                else if(sc & SC_ScrollBarSubLine)
                {
                    pixmap.load(":/qss/icons/scrolluparrow.png");
                }
                else
                {
                    pixmap.load(":/qss/icons/scrolluparrow.png");
                }
            }

            painter->drawPixmap(drawRect, pixmap);
        }


        if (sub & SC_ScrollBarSlider)
        {
            drawRect = subControlRect(CC_ScrollBar, option, SC_ScrollBarSlider, widget);
            QPainterPath painterPath;
            painterPath.addRoundedRect(drawRect.left(), drawRect.top(), drawRect.width(), drawRect.height(), 4, 4);

            if(sc & SC_ScrollBarSlider)
            {
                painter->fillPath(painterPath, bkSliderPress);
            }
            else
            {
                painter->fillPath(painterPath, bkSliderHover);
            }
        }
    }

    painter->restore();
}


