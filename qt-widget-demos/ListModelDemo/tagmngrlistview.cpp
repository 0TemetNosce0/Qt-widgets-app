#include <QDrag>
#include <QDebug>
#include <QMimeData>
#include <QDropEvent>
#include <QDragEnterEvent>

#include "tagmngrlistview.h"
#include "tagmngrlistmodel.h"


TagMngrListView::TagMngrListView(QWidget *parent)
    : QListView(parent)
{

}

void TagMngrListView::startDrag(Qt::DropActions supportedActions)
{
    QModelIndexList list = this->selectionModel()->selectedIndexes();

    TagMngrListModel *tagmodel = dynamic_cast<TagMngrListModel*>(this->model());
    QMimeData *data = tagmodel->mimeData(list);

    if(!data)
    {
        qDebug() << "Error! no data obtained!";
        return;
    }

    QDrag *drag = new QDrag(this);
    drag->setMimeData(data);
    drag->exec(supportedActions, Qt::IgnoreAction);
}

void TagMngrListView::dragEnterEvent(QDragEnterEvent *event)
{
    setState(DraggingState);
    event->accept();
}

void TagMngrListView::dropEvent(QDropEvent *e)
{
    qDebug() << e->mimeData();

    QModelIndex index = indexVisuallyAt(e->pos());
    TagMngrListModel *tagmodel = dynamic_cast<TagMngrListModel*>(this->model());

    tagmodel->dropMimeData(e->mimeData(), e->dropAction(), index.row(), index.column(), index.parent());

    //QListView::dropEvent(e);
}

QModelIndex TagMngrListView::indexVisuallyAt(const QPoint& p)
{
    if (viewport()->rect().contains(p))
    {
        QModelIndex index = indexAt(p);

        if (index.isValid() && visualRect(index).contains(p))
        {
            return index;
        }
    }

    return QModelIndex();
}
