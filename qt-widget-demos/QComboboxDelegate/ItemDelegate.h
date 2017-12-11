#ifndef ITEMDELEGATE_H
#define ITEMDELEGATE_H

#include <QStyledItemDelegate>

class ItemDelegate : public QStyledItemDelegate
{
  Q_OBJECT

signals:
    void deleteItem(const QModelIndex &index);

public:
    ItemDelegate(QObject * parent=0);
    virtual ~ItemDelegate(){}

protected:
    void paint(QPainter * painter,const QStyleOptionViewItem & option,const QModelIndex & index) const;
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);
};

#endif // ITEMDELEGATE_H
