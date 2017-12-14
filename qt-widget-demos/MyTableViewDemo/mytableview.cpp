#include "mytableview.h"
#include "ui_mytableview.h"
#include <QPainter>
#include <QMouseEvent>
#include "MyTableView.h"

#ifndef NDEBUG
#include<QDebug>
#endif

MyTableView::MyTableView(QWidget * parent)
    :QTableView(parent)
{
    delegate = new MyItemDelegate;
    model = new MyStandardItemModel;
    model->setRowCount(6);
    model->setColumnCount(8);

    this->setModel(model);
    this->setItemDelegate(delegate);

    this->resizeColumnsToContents();
    this->resizeRowsToContents();
    this->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->setMouseTracking(true);//important
}

void MyTableView::mouseMoveEvent(QMouseEvent * event)
{
    int column = this->columnAt(event->x());
    int row = this->rowAt(event->y());

    if(column == 0 && row != -1)
    {
        this->setCursor(Qt::PointingHandCursor);
    }
    else
    {
        this->setCursor(Qt::ArrowCursor);
    }
}

MyItemDelegate::MyItemDelegate(QObject * parent)
    :QItemDelegate(parent)
{
    favouritePixmap = QPixmap(":/favourite.png");
    notFavouritePixmap = QPixmap(":/no-favourite.png");
}

void MyItemDelegate::paint(QPainter * painter,
        const QStyleOptionViewItem & option,
        const QModelIndex & index) const
{
    if(index.column()!=0)
    {
        QItemDelegate::paint(painter,option,index);
        return;
    }
    const QAbstractItemModel *model = index.model();
    QVariant var = model->data(index,Qt::CheckStateRole);

    if(var.isNull())
    {
        var = false;
    }
    const QPixmap &star = var.toBool() ? favouritePixmap : notFavouritePixmap;
    int width = star.width();
    int height = star.height();
    QRect rect = option.rect;
    int x = rect.x() + rect.width()/2 - width/2;
    int y = rect.y() + rect.height()/2 - height/2;

    painter->drawPixmap(x,y,star);
}

bool MyItemDelegate::editorEvent(QEvent * event,
        QAbstractItemModel * model,
        const QStyleOptionViewItem & /*option*/,
        const QModelIndex & index)
{
    if(event->type() == QEvent::MouseButtonPress && index.column() == 0)
    {
        QVariant var = model->data(index,Qt::CheckStateRole);
        bool isFavourite = var.toBool();

        if(var.isValid())
        {
            isFavourite = isFavourite ? false : true;
        }
        else
        {
            isFavourite = true;
        }

        model->setData(index,isFavourite, Qt::CheckStateRole);
        return true;//I have handled the event
    }

    return false;
}

QVariant MyStandardItemModel::data(
        const QModelIndex & index,
        int role) const
{
    int column = index.column();

    if(role == Qt::DisplayRole && column!=0)
    {
        return column + 1;
    }

    if(role == Qt::ToolTipRole && column==0)
    {
        return QStringLiteral("love");
    }

    return QStandardItemModel::data(index,role);
}

QVariant MyStandardItemModel::headerData(int section,
        Qt::Orientation orientation, int role) const
{
    if(section == 0 && orientation == Qt::Horizontal)
    {
        if(role == Qt::DecorationRole)
        {
            return QIcon(":/favourite.png");
        }
        if(role == Qt::DisplayRole)
        {
            return "";
        }
        if(role == Qt::ToolTipRole)
        {
            return QStringLiteral("love");
        }
    }
    return QStandardItemModel::headerData(section,orientation,role);
}
