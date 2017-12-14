
#include "myDockTitleBar.h"

MyDockTitleBar::MyDockTitleBar(QWidget *parent)
    : QWidget(parent)
{
    minPix = style()->standardPixmap(QStyle::SP_TitleBarMinButton);
    closePix  = style()->standardPixmap(QStyle::SP_TitleBarCloseButton);
    floatPix = style()->standardPixmap(QStyle::SP_TitleBarNormalButton);
}

QSize MyDockTitleBar::minimumSizeHint() const
{
    QDockWidget *dw = qobject_cast<QDockWidget*>(parentWidget());
    Q_ASSERT(dw != 0);
    QSize result(200, 35);

    if (dw->features() & QDockWidget::DockWidgetVerticalTitleBar)
    {
        result.transpose();
    }

    return result;
}

void MyDockTitleBar::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QRect rect = this->rect();

    QDockWidget *dw = qobject_cast<QDockWidget*>(parentWidget());
    Q_ASSERT(dw != 0);

    if (dw->features() & QDockWidget::DockWidgetVerticalTitleBar)
    {
        QSize s = rect.size();
        s.transpose();
        rect.setSize(s);

        painter.translate(rect.left(), rect.top() + rect.width());
        painter.rotate(-90);
        painter.translate(-rect.left(), -rect.top());
    }

    painter.fillRect(rect.left(), rect.top(), rect.width(), rect.height(), QColor(tr("white")));
    painter.drawPixmap(rect.topRight() - QPoint(closePix.width() + 10, -10), closePix);
    painter.drawPixmap(rect.topRight() - QPoint(minPix.width() + 10 + closePix.width() + 10, -7), minPix);
    painter.drawPixmap(rect.topRight() - QPoint(floatPix.width() + 10 + minPix.width() + 10
                                                + closePix.width() + 10, -10), floatPix);
}

void MyDockTitleBar::mousePressEvent(QMouseEvent *event)
{
    QPoint pos = event->pos();

    QRect rect = this->rect();

    QDockWidget *dw = qobject_cast<QDockWidget*>(parentWidget());
    Q_ASSERT(dw != 0);

    if (dw->features() & QDockWidget::DockWidgetVerticalTitleBar)
    {
        QPoint p = pos;
        pos.setX(rect.left() + rect.bottom() - p.y());
        pos.setY(rect.top() + p.x() - rect.left());

        QSize s = rect.size();
        s.transpose();
        rect.setSize(s);
    }

    const int buttonRight = 10;
    const int buttonWidth = 20;
    int right = rect.right() - pos.x();
    int button = (right - buttonRight)/buttonWidth;

    qDebug() << rect.right() << " --- " << pos.x() << " --- " << right << " --- " << button;

    switch (button)
    {
    case 0:
        event->accept();
        dw->close();
        break;
    case 1:
        event->accept();
        dw->setFloating(!dw->isFloating());
        break;
    case 2:
    {
        event->accept();
        QDockWidget::DockWidgetFeatures features = dw->features();
        if (features & QDockWidget::DockWidgetVerticalTitleBar)
        {
            features &= ~QDockWidget::DockWidgetVerticalTitleBar;
        }
        else
        {
            features |= QDockWidget::DockWidgetVerticalTitleBar;
        }
        dw->setFeatures(features);
        break;
    }
    default:
        event->ignore();
        break;
    }
}

void MyDockTitleBar::updateMask()
{
    //    QDockWidget *dw = qobject_cast<QDockWidget*>(parent());
    //    Q_ASSERT(dw != 0);

    //    QRect rect = dw->rect();
    //    QPixmap bitmap(dw->size());

    //    {
    //        QPainter painter(&bitmap);

    //        ///initialize to transparent
    //        painter.fillRect(rect, Qt::color0);

    //        QRect contents = rect;
    //        contents.setTopLeft(geometry().bottomLeft());
    //        contents.setRight(geometry().right());
    //        contents.setBottom(contents.bottom()-y());
    //        painter.fillRect(contents, Qt::color1);



    //        //let's pait the titlebar

    //        QRect titleRect = this->geometry();

    //        if (dw->features() & QDockWidget::DockWidgetVerticalTitleBar) {
    //            QSize s = rect.size();
    //            s.transpose();
    //            rect.setSize(s);

    //            QSize s2 = size();
    //            s2.transpose();
    //            titleRect.setSize(s2);

    //            painter.translate(rect.left(), rect.top() + rect.width());
    //            painter.rotate(-90);
    //            painter.translate(-rect.left(), -rect.top());
    //        }

    //        contents.setTopLeft(titleRect.bottomLeft());
    //        contents.setRight(titleRect.right());
    //        contents.setBottom(rect.bottom()-y());

    //        QRect rect = titleRect;


    //        painter.drawPixmap(rect.topLeft(), leftPm.mask());
    //        painter.fillRect(rect.left() + leftPm.width(), rect.top(),
    //                         rect.width() - leftPm.width() - rightPm.width(),
    //                         centerPm.height(), Qt::color1);
    //        painter.drawPixmap(rect.topRight() - QPoint(rightPm.width() - 1, 0), rightPm.mask());

    //        painter.fillRect(contents, Qt::color1);
    //    }

    //    dw->setMask(bitmap);
}
