#include "mywidget.h"
#include <Windows.h>
#include "myshowwidget.h"
#include <QDebug>
#include <QPainter>
MyWidget::MyWidget(QWidget *parent):QWidget(parent)
  ,test(new MyShowWidget(this))
{
    //鼠标穿透

//    DWORD dwExStyle = GetWindowLong((HWND)winId(), GWL_EXSTYLE) |WS_EX_TRANSPARENT | WS_EX_LAYERED;
//               DWORD dwNewStyle = dwExStyle;
//               dwNewStyle &= ~WS_EX_TRANSPARENT;
//    SetWindowLong((HWND)winId(), GWL_EXSTYLE, dwExStyle/*GetWindowLong((HWND)winId(), GWL_EXSTYLE) |WS_EX_TRANSPARENT | WS_EX_LAYERED*/);
//    SetWindowLong((HWND)winId(), GWL_EXSTYLE, GetWindowLong((HWND)winId(), GWL_EXSTYLE) |
//                   WS_EX_TRANSPARENT | WS_EX_LAYERED);
    this->setWindowFlags(Qt::FramelessWindowHint/*|Qt::WindowStaysOnTopHint|Qt::Tool*/);//WindowStaysOnTopHint置顶，Tool任务栏隐藏
    //透明
    this->setAttribute(Qt::WA_TranslucentBackground, true);//透明，如果标题栏隐藏没有影藏，则是透明是黑色的
//    this->setStyleSheet("background-color: transparent;");
//    ModifyStyleEx(0,WS_EX_LAYERED);
//    SetLayeredWindowAttributes((HWND)winId(),0,233,LWA_ALPHA);

//    LONG nRet = ::GetWindowLong((HWND)(this->winId()), GWL_EXSTYLE);
//    nRet = nRet | WS_EX_LAYERED /*|WS_CLIPCHILDREN*/;
//    ::SetWindowLong((HWND)(this->winId()), GWL_EXSTYLE, nRet);
//    SetLayeredWindowAttributes((HWND)(this->winId()), 0,  100, LWA_ALPHA);
//////    setAttribute(Qt::WA_TranslucentBackground, true);
    SetWindowLong((HWND)(this->winId()), GWL_EXSTYLE, GetWindowLong((HWND)(this->winId()), GWL_EXSTYLE) /*| WS_EX_NOACTIVATE*/ |WS_EX_TRANSPARENT);

//    long style = GetWindowLong((HWND)(this->winId()),GWL_STYLE);
//    style     &= ~(WS_CAPTION);
//    SetWindowLong((HWND)(this->winId()),GWL_STYLE,style);
    //this->setWindowFlags(Qt::FramelessWindowHint);
//    this->setAttribute(Qt::WA_TranslucentBackground, true);//透明，如果标题栏隐藏没有影藏，则是透明是黑色的
    //设置窗体中所有单色区域都透明
//    SetLayeredWindowAttributes((HWND)(this->winId()),RGB(10, 300, 300),0,LWA_COLORKEY);
    setGeometry(QRect(10,10,400,400));
    test->setGeometry(QRect(10,10,100,100));
    //    test->setStyleSheet("background-color: blue;");
}

void MyWidget::mousePressEvent(QMouseEvent *event)
{
    qDebug("2222222");
}

void MyWidget::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
//    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
qDebug("11111");
//    return QWidget::paintEvent(event);
//    qDebug("2222222222");

//    QPainter p(this);
    p.setPen(QPen(/*QColor(Qt::yellow)*/Qt::NoPen));
    p.setBrush(QBrush(QColor(255,22,255,100)));
    p.drawRect(QRect(10,10,200,200));
//         p.setCompositionMode( QPainter::CompositionMode_Clear );
//         p.fillRect( 10, 10, 300, 300, Qt::SolidPattern );
//    QWidget::paintEvent(event);
}
