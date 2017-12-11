#include "installedappdelegate.h"
#include <QDebug>
#include <QPainter>
#include <QStyleOptionButton>
#include <QApplication>
#include <QCheckBox>
#include "downloadingitem.h"

InstalledAppDelegate::InstalledAppDelegate(QObject *parent)
    : QItemDelegate(parent)
{

}

void InstalledAppDelegate::paint(QPainter *painter,
                                 const QStyleOptionViewItem &option,
                                 const QModelIndex &index) const
{
    bool checked = index.model()->data(index, Qt::CheckStateRole).toBool();

    if (checked)
    {
        painter->save();
        painter->drawImage(option.rect, QImage("select.png"));
        painter->restore();
    }

    if (index.column() == 1)
    {
        QString name = index.model()->data(index, Qt::UserRole+1).toString();
        QString icon = index.model()->data(index, Qt::UserRole+2).toString();
        painter->save();
        painter->drawImage(option.rect.x() + 8, option.rect.y() + 7, QImage(icon));
        painter->drawText(option.rect.x()+68, option.rect.y()+35, name);
        painter->restore();
    }
    else if (index.column() == 0)
    {
        painter->save();
        painter->drawImage(option.rect.x() + 5, option.rect.y() + 25, QImage("checkbox.png"));

        if (checked)
        {
            painter->drawImage(option.rect.x() + 5, option.rect.y() + 25, QImage("checked.png"));
        }

        painter->restore();
    }
}

QSize InstalledAppDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QSize(100, 150);
}

QWidget *InstalledAppDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &index) const
{
    if (index.column() == 2)
    {
        downloadingitem *item = new downloadingitem(parent);
        item->setItemIndex(index);
        connect(item, SIGNAL(pauseButtonClicked()),
                this, SLOT(handlePauseButtonClicked()));
        connect(item, SIGNAL(removeButtonClicked()),
                this, SLOT(handleRemoveButtonClicked()));
        connect(item, SIGNAL(startButtonClicked()),
                this, SLOT(handleStartButtonClicked()));
        return item;
    }
    return NULL;
}

void InstalledAppDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{

}

void InstalledAppDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{

}

void InstalledAppDelegate::handleStartButtonClicked()
{
    qDebug() << "start button clicked" << endl;
}

void InstalledAppDelegate::handleRemoveButtonClicked()
{
    qDebug() << "remove button clicked" << endl;
}

void InstalledAppDelegate::handlePauseButtonClicked()
{
    qDebug() << "pause button clicked" << endl;
}
