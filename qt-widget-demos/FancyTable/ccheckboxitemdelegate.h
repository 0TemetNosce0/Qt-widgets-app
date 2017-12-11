#ifndef CCHECKBOXITEMDELEGATE_H
#define CCHECKBOXITEMDELEGATE_H

#include <QStyledItemDelegate>

class cCheckBoxItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    cCheckBoxItemDelegate(QObject *parent = 0);

protected:
    void paint(QPainter* painter, const QStyleOptionViewItem & option, const QModelIndex & index) const;
    virtual bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);
    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;

signals:

public slots:

};

#endif // CCHECKBOXITEMDELEGATE_H
