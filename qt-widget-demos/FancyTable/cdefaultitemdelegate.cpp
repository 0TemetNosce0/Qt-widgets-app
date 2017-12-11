#include "cdefaultitemdelegate.h"
#include <QPainter>

cDefaultItemDelegate::cDefaultItemDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{

}

void cDefaultItemDelegate::paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
    // actually this one draws the grid
    painter->setPen(QColor(200,200,200));
    painter->drawRect(option.rect);
    QStyledItemDelegate::paint(painter, option, index);
}
