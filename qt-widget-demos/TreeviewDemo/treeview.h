#ifndef TREEVIEW_H
#define TREEVIEW_H

#include <QtGui>
#include <QTreeView>

class TreeView : public QTreeView
{
public:
    TreeView();
    void iterateOverItems();
    QList<QStandardItem*> returnTheItems();
    void mouseDoubleClickEvent(QMouseEvent *event);

private:
    QStandardItemModel *model;
};

#endif // TREEVIEW_H
