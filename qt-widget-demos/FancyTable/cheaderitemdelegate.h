#ifndef CHEADERITEMDELEGATE_H
#define CHEADERITEMDELEGATE_H

#include <QStyledItemDelegate>

class cHeaderItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    cHeaderItemDelegate(QObject *parent = 0);

protected:
    void paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const;
    virtual bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);
    QWidget * createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;

signals:

public slots:

};

#endif // CHEADERITEMDELEGATE_H
