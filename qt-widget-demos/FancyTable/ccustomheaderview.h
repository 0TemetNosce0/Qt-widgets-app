#ifndef CCUSTOMHEADERVIEW_H
#define CCUSTOMHEADERVIEW_H

#include <QHeaderView>
#include "crect.h"

class cCustomHeaderView : public QHeaderView
{
    Q_OBJECT

public:
    enum HeaderDataModelRoles
    {
        HorizontalHeaderDataRole = Qt::UserRole,
        VerticalHeaderDataRole = Qt::UserRole + 1
    };

    explicit cCustomHeaderView(QWidget *parent = 0);

    QModelIndex indexAt(const QPoint &pos) const;

    int sectionSizes();
    int sectionSizes(int lIndex, int sectionCount);

    void setHoverIndex(const QPersistentModelIndex &index);

protected:
    QSize sectionSizeFromContents(int logicalIndex) const;
    void paintEvent(QPaintEvent *e);
    bool viewportEvent(QEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *e);
    bool event(QEvent *e);

private:
    QList<cRect> m_RectList;
    QModelIndex mHover;

public slots:
    void onSectionResized(int logicalIndex, int oldSize, int newSize);
};

#endif // CCUSTOMHEADERVIEW_H
