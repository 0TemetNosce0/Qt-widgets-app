#include "QDockArrows.h"
#include <QPainter>
#include <QDrag>
#include <QMimeData>
#include <QDragEnterEvent>
#include <QDragLeaveEvent>


class QArrowWidget : public QWidget
{
public:
    explicit QArrowWidget(const char* imgPath, QDockArrows* arrows, DockArea area, QWidget* parent)
        : QWidget(parent, Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint)
        , pixmap(imgPath)
        , arrows_(arrows)
        , area_(area)
    {
        setAttribute(Qt::WA_TranslucentBackground);
        resize(pixmap.size());
    }

private:
    QPixmap pixmap;
    QDockArrows* arrows_;
    DockArea area_;
protected:
    void paintEvent(QPaintEvent *)
    {
        QPainter painter(this);
        painter.drawPixmap(0, 0, pixmap);
    }
};


QDockArrows::QDockArrows(QWidget *parent)
    : QObject(parent)
    , leftWid(new QArrowWidget("://ArrowPics/left.png", this, LeftArea, parent))
    , rightWid(new QArrowWidget("://ArrowPics/right.png", this, RightArea, parent))
    , topWid(new QArrowWidget("://ArrowPics/top.png", this, TopArea, parent))
    , bottomWid(new QArrowWidget("://ArrowPics/bottom.png", this, BottomArea, parent))
    , centerWid(new QArrowWidget("://ArrowPics/center.png", this, CenterArea, parent))
    , centerLeftWid(new QArrowWidget("://ArrowPics/left.png", this, CenterLeftArea, parent))
    , centerRightWid(new QArrowWidget("://ArrowPics/right.png", this, CenterRightArea, parent))
    , centerTopWid(new QArrowWidget("://ArrowPics/top.png", this, CenterTopArea, parent))
    , centerBottomWid(new QArrowWidget("://ArrowPics/bottom.png", this, CenterBottomArea, parent))
    , parentWid(parent)
{
    leftWid->hide();
    rightWid->hide();
    topWid->hide();
    bottomWid->hide();
    centerWid->hide();
    centerLeftWid->hide();
    centerRightWid->hide();
    centerTopWid->hide();
    centerBottomWid->hide();
}

void QDockArrows::show(int dockArea)
{
    int w = parentWid->width();
    int h = parentWid->height();

    if (dockArea & LeftArea)
    {
        leftWid->move(0, (h - leftWid->height()) / 2);
        leftWid->show();
        leftWid->raise();
    }
    else
    {
        leftWid->hide();
    }

    if (dockArea & RightArea)
    {
        rightWid->move(w - rightWid->width(), (h - rightWid->height()) / 2);
        rightWid->show();
        rightWid->raise();
    }
    else
    {
        rightWid->hide();
    }

    if (dockArea & TopArea)
    {
        topWid->move((w - rightWid->width()) / 2, 0);
        topWid->show();
        topWid->raise();
    }
    else
    {
        topWid->hide();
    }

    if (dockArea & BottomArea)
    {
        bottomWid->move((w - rightWid->width()) / 2, h - bottomWid->height());
        bottomWid->show();
        bottomWid->raise();
    }
    else
    {
        bottomWid->hide();
    }

    if (dockArea & CenterArea)
    {
        centerWid->move((w - centerWid->width()) / 2, (h - leftWid->height()) / 2);
        centerWid->show();
        centerWid->raise();
    }
    else
    {
        centerWid->hide();
    }

    if (dockArea & CenterLeftArea)
    {
        centerLeftWid->move((w - centerLeftWid->width()) / 2 - centerLeftWid->width(), (h - centerLeftWid->height()) / 2);
        centerLeftWid->show();
        centerLeftWid->raise();
    }
    else
    {
        centerLeftWid->hide();
    }

    if (dockArea & CenterRightArea)
    {
        centerRightWid->move((w - centerRightWid->width()) / 2 + centerRightWid->width(), (h - centerRightWid->height()) / 2);
        centerRightWid->show();
        centerRightWid->raise();
    }
    else
    {
        centerRightWid->hide();
    }

    if (dockArea & CenterTopArea)
    {
        centerTopWid->move((w - centerTopWid->width()) / 2, (h - centerTopWid->height()) / 2 - centerTopWid->height());
        centerTopWid->show();
        centerTopWid->raise();
    }
    else
    {
        centerTopWid->hide();
    }

    if (dockArea & CenterBottomArea)
    {
        centerBottomWid->move((w - centerBottomWid->width()) / 2, (h - centerBottomWid->height()) / 2 + centerBottomWid->height());
        centerBottomWid->show();
        centerBottomWid->raise();
    }
    else
    {
        centerBottomWid->hide();
    }
}

DockArea QDockArrows::getDockAreaByPos(QPoint pos)
{
    if (leftWid->isVisible() && leftWid->geometry().contains(pos))
    {
        return LeftArea;
    }

    if (rightWid->isVisible() && rightWid->geometry().contains(pos))
    {
        return RightArea;
    }

    if (topWid->isVisible() && topWid->geometry().contains(pos))
    {
        return TopArea;
    }

    if (bottomWid->isVisible() && bottomWid->geometry().contains(pos))
    {
        return BottomArea;
    }

    if (centerWid->isVisible() && centerWid->geometry().contains(pos))
    {
        return CenterArea;
    }

    if (centerLeftWid->isVisible() && centerLeftWid->geometry().contains(pos))
    {
        return CenterLeftArea;
    }

    if (centerRightWid->isVisible() && centerRightWid->geometry().contains(pos))
    {
        return CenterRightArea;
    }

    if (centerTopWid->isVisible() && centerTopWid->geometry().contains(pos))
    {
        return CenterTopArea;
    }

    if (centerBottomWid->isVisible() && centerBottomWid->geometry().contains(pos))
    {
        return CenterBottomArea;
    }

    return NoneArea;
}
