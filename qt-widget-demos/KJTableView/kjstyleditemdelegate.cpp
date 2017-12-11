#include "kjstyleditemdelegate.h"

#include <QDebug>
#include <QPainter>
#include <QApplication>
#include <QStyledItemDelegate>
#include <QStyleOptionViewItem>

KJStyledItemDelegate::KJStyledItemDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
    for (int i = 0; i < 30; i++)
    {
        KJConversationWidget *widget = new KJConversationWidget();
        widget->widgetIndex = i;
        widget->setHidden(true);
        widgets.append(widget);
    }
}

void KJStyledItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    // re-layout widget
    Q_UNUSED(painter);
    KJConversationWidget *widget = this->widgets.at(index.row() % widgets.count());
    widget->init(QString("Conversation %1").arg(index.row()), QString("Detail %1").arg(index.row()%widgets.count()), index.row());
    widget->setGeometry(option.rect);

    // hide unneccessaray widget
    for (int i = 0; i < widgets.count(); i++)
    {
        KJConversationWidget *widget = this->widgets.at(i);

        if (widget->geometry().x() != 0)
        {
            widget->setGeometry(QRect(10000,10000,0,0));
        }
    }
}

QSize KJStyledItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);
    return option.rect.size();
}

void KJStyledItemDelegate::refreshWidgets(bool hide)
{
    for (int i = 0; i < 30; i++)
    {
        widgets.at(i)->setHidden(hide);
    }
}
