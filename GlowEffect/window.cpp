#include "window.h"
#include <QLabel>
#include <QHBoxLayout>
#include "gloweffect.h"
#include <QToolTip>


Window::Window(QWidget *parent)
    : QWidget(parent)
{
    lbl = new QLabel("Let's have a try!", this);
    QHBoxLayout * layout = new QHBoxLayout(this);
    layout->addWidget(lbl);
    setLayout(layout);

    setFont(QToolTip::font());

    GlowEffect *effect = new GlowEffect(this);//创建，this只是父对象管理的
    effect->setRadius(5);
    effect->setGlowColor(Qt::blue);
    lbl->setGraphicsEffect(effect);//lbl设置effect，显示由effect 的draw来显示。
//    lbl->setGraphicsEffect(0);//删除effect。
}

Window::~Window()
{
}
