#ifndef KJSTYLEDITEMDELEGATE_H
#define KJSTYLEDITEMDELEGATE_H

#include <QLabel>
#include <QTableView>
#include <QPushButton>
#include <QStyledItemDelegate>

#include "kjconversationwidget.h"

class KJStyledItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit KJStyledItemDelegate(QObject *parent = 0);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;

    void refreshWidgets(bool hide);

public:
    QTableView *tableView;
    QList<KJConversationWidget*> widgets;

private:

signals:

public slots:

};

#endif // KJSTYLEDITEMDELEGATE_H
