#include "widget.h"
#include "ui_widget.h"
#include <QDesktopWidget>
#include <QSignalTransition>
#include <QPropertyAnimation>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    mResized = false;
    resize(640,480);

    QDesktopWidget* desktop = QApplication::desktop(); // =qApp->desktop();р╡©ирт
    move((desktop->width() - this->width())/2, (desktop->height() - this->height())/2);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::resizeEvent(QResizeEvent* event)
{
    Q_UNUSED(event);

    if(size().height() == 0)
    {
        close();
        return;
    }

    if(mResized)
    {
        return;
    }

    mButton = new QPushButton(this);
    mButton->setText("Click");

    mResized = true;
    QPoint p = pos();
    QSize s = size();

    mMachine = new QStateMachine(this);
    mMaxState = new QState(mMachine);
    mMaxState->assignProperty(this,"geometry",QRect(p,s));
    //connect(mMachine,SIGNAL(finished()),this,SLOT(callClose()));

    mMinState = new QState(mMachine);
    mMinState->assignProperty(this,"geometry",QRect(p.x(),p.y()+s.height()/2,s.width(),0));
    //connect(mMinState,SIGNAL(entered()),this,SLOT(callClose()));
    mMachine->setInitialState(mMaxState);

    QPropertyAnimation* ani1 = new QPropertyAnimation(this,"geometry");
    ani1->setDuration(300);
    ani1->setEasingCurve(QEasingCurve::Linear);

    QSignalTransition* transition = mMaxState->addTransition(mButton,SIGNAL(clicked()),mMinState);
    transition->addAnimation(ani1);

    mMachine->start();
}
