#ifndef CDEFAULTITEMDELEGATE_H
#define CDEFAULTITEMDELEGATE_H

#include <QStyledItemDelegate>

class cDefaultItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit cDefaultItemDelegate(QObject *parent = 0);

protected:
    void paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const;

signals:

public slots:

};

#endif // CDEFAULTITEMDELEGATE_H
