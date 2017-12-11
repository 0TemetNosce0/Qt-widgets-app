#include "ItemDelegate.h"
#include <QPainter>
#include <QMouseEvent>
#include <QStyledItemDelegate>
#include <QToolTip>
#include <QApplication>

ItemDelegate::ItemDelegate(QObject * parent)
    : QStyledItemDelegate(parent)
{

}

void ItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItem  viewOption(option);
    if (viewOption.state & QStyle::State_HasFocus)
    {
        viewOption.state = viewOption.state ^ QStyle::State_HasFocus;
    }

    QStyledItemDelegate::paint(painter, viewOption, index);

    int height = (viewOption.rect.height() - 9) / 2;
    QPixmap pixmap = QPixmap(":/delete");
    QRect decorationRect = QRect(viewOption.rect.left() + viewOption.rect.width() - 30, viewOption.rect.top() + height, 9, 9);
    painter->drawPixmap(decorationRect, pixmap);
}

bool ItemDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    int height = (option.rect.height() - 9) / 2;
    QRect decorationRect = QRect(option.rect.left() + option.rect.width() - 30, option.rect.top() + height, 9, 9);

    QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
    if (event->type() == QEvent::MouseButtonPress && decorationRect.contains(mouseEvent->pos()))
    {
        emit deleteItem(index);
    }

    if (event->type() == QEvent::MouseMove && decorationRect.contains(mouseEvent->pos()))
    {
        QCursor cursor(Qt::PointingHandCursor);
        QApplication::setOverrideCursor(cursor);
        QString strText = QStringLiteral("É¾³ýÕËºÅÐÅÏ¢");
        QToolTip::showText(mouseEvent->globalPos(), strText);
    }
    else
    {
        QCursor cursor(Qt::ArrowCursor);
        QApplication::setOverrideCursor(cursor);
    }

    return QStyledItemDelegate::editorEvent(event, model, option, index);
}
