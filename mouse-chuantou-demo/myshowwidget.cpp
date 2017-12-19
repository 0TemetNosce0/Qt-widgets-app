#include "myshowwidget.h"
#include <QPainter>
#include <QDebug>
#include <QPushButton>
#include <QStyleOption>
#include <Windows.h>
MyShowWidget::MyShowWidget(QWidget *parent)
    :QWidget(parent)
{
// setAttribute(Qt::WA_TransparentForMouseEvents,true);
//        DWORD dwExStyle = GetWindowLong((HWND)winId(), GWL_EXSTYLE) |WS_EX_TRANSPARENT | WS_EX_LAYERED;
//                   DWORD dwNewStyle = dwExStyle;
//                   dwNewStyle &= ~WS_EX_TRANSPARENT;
//        SetWindowLong((HWND)winId(), GWL_EXSTYLE, dwExStyle/*GetWindowLong((HWND)winId(), GWL_EXSTYLE) |WS_EX_TRANSPARENT | WS_EX_LAYERED*/);
//setMouseTracking();
//    setAttribute(Qt::WA_TransparentForMouseEvents,true);
//    QPushButton
//    setAutoFillBackground(true);
//    SetWindowLong((HWND)winId(), GWL_EXSTYLE, GetWindowLong((HWND)winId(), GWL_EXSTYLE) |
//                  WS_EX_TRANSPARENT | WS_EX_LAYERED);
//setAttribute(Qt::WA_DontCreateNativeAncestors);
//    LONG nRet = ::GetWindowLong((HWND)(this->winId()), GWL_EXSTYLE);
//    nRet = nRet | WS_EX_LAYERED;
//    ::SetWindowLong((HWND)(this->winId()), GWL_EXSTYLE, nRet);
//    SetLayeredWindowAttributes((HWND)(this->winId()), 0,  100, LWA_ALPHA);
//    //setAttribute(Qt::WA_TranslucentBackground, true);
//    SetWindowLong((HWND)(this->winId()), GWL_EXSTYLE, GetWindowLong((HWND)(this->winId()), GWL_EXSTYLE) | WS_EX_NOACTIVATE |WS_EX_TRANSPARENT);

}

void MyShowWidget::paintEvent(QPaintEvent *event)
{


//    QStyleOption opt;
//    opt.init(this);
    qDebug("22222222");
    QPainter p(this);
//    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

//    return QWidget::paintEvent(event);
//    qDebug("2222222222");

//    QPainter p(this);
    p.setPen(QPen(QColor(Qt::red)));
    p.setBrush(QBrush(QColor(Qt::red)));
    p.drawRect(QRect(10,10,100,100));

//    QWidget::paintEvent(event);
//    this->parent()
}
