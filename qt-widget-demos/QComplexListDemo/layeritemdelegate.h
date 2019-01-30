#ifndef LAYERITEMDELEGATE_H
#define LAYERITEMDELEGATE_H

#include <QDebug>
#include <QPainter>
#include <QLineEdit>
#include <QStyledItemDelegate>

class LayerItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    LayerItemDelegate(QObject *parent=0);
    ~LayerItemDelegate();


    void paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const;
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
        const QModelIndex &index) const;
    bool editorEvent(QEvent * event,
        QAbstractItemModel * model,
        const QStyleOptionViewItem & option,
        const QModelIndex & index);
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
        const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor,
        const QStyleOptionViewItem &option, const QModelIndex &index) const;
//    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);

private:
    QPixmap m_gridPixmap;
};

#endif // LAYERITEMDELEGATE_H
