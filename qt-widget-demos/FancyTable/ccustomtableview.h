#ifndef CCUSTOMTABLEVIEW_H
#define CCUSTOMTABLEVIEW_H

#include <QTableView>
#include "ccustomheadermodel.h"
#include <QEvent>
#include <QAbstractItemView>

class cCustomTableView : public QTableView
{
    Q_OBJECT

public:
    explicit cCustomTableView(QWidget *parent = 0);

    QModelIndex indexAt(const QPoint &pos) const;
    QRect visualRect(const QModelIndex &index) const;

    QModelIndex moveCursor(CursorAction cursorAction, Qt::KeyboardModifiers modifiers);

protected:
    void paintEvent(QPaintEvent *event);
    bool viewportEvent(QEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    int sectionSizes(QHeaderView *hv, int col, int colSpan) const;

    void setHoverIndex(const QPersistentModelIndex &index);
    QModelIndex mHover;

protected slots:
    void columnResized(int column, int oldWidth, int newWidth);
};

#endif // CCUSTOMTABLEVIEW_H
