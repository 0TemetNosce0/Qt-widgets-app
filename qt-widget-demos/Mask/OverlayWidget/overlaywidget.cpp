#include "overlaywidget.h"
#include "ui_overlaywidget.h"

#include <QPainter>
#include <QResizeEvent>

OverlayWidget::OverlayWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OverlayWidget)
{
    ui->setupUi(this);

    if (parent)
    {
        parent->installEventFilter(this);
        raise();
    }
}

OverlayWidget::~OverlayWidget()
{
    delete ui;
}

bool OverlayWidget::eventFilter(QObject *obj, QEvent *ev)
{
    if (obj == parent())
    {
        if (ev->type() == QEvent::Resize)
        {
            QResizeEvent * rev = static_cast<QResizeEvent*>(ev);
            resize(rev->size());
        }
        else if (ev->type() == QEvent::ChildAdded)
        {
            raise();
        }
    }

    return QWidget::eventFilter(obj, ev);
}

bool OverlayWidget::event(QEvent *ev)
{
    if (ev->type() == QEvent::ParentAboutToChange)
    {
        if (parent()) parent()->removeEventFilter(this);
    }
    else if (ev->type() == QEvent::ParentChange)
    {
        if (parent())
        {
            parent()->installEventFilter(this);
            raise();
        }
    }

    return QWidget::event(ev);
}


LoadingOverlay::LoadingOverlay(QWidget *parent)
    : OverlayWidget(parent)
{
    setAttribute(Qt::WA_TranslucentBackground);
}

void LoadingOverlay::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.fillRect(rect(), QColor(100, 100, 100, 128));
    p.setPen(QColor(200, 200, 255, 255));
    p.setFont(QFont("arial,helvetica", 48));
    p.drawText(rect(), "Loading...", Qt::AlignHCenter | Qt::AlignVCenter);
}


ContainerWidget::ContainerWidget(QWidget *parent)
    : QWidget(parent)
{

}

bool ContainerWidget::event(QEvent *ev)
{
    if (ev->type() == QEvent::ChildAdded)
    {
        setSize(static_cast<QChildEvent*>(ev)->child());
    }

    return QWidget::event(ev);
}

void ContainerWidget::resizeEvent(QResizeEvent *)
{
    foreach(QObject * obj, children())
    {
        setSize(obj);
    }
}
