#ifndef BOOLEANDELEGATE_H
#define BOOLEANDELEGATE_H

#include <QStyledItemDelegate>

#include "centeredcheckboxwidget.h"

class BooleanDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit BooleanDelegate(QObject *parent, bool defaultValue = true);

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const;

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const;

    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const;

    void updateEditorGeometry(QWidget *editor,
                              const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:
    bool defaultValue;
};

#endif // BOOLEANDELEGATE_H
