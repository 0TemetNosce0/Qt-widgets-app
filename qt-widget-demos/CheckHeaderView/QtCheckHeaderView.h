#ifndef QTCHECKHEADERVIEW_H
#define QTCHECKHEADERVIEW_H

#include <QHeaderView>
#include <QList>
#include <QMap>

class QAbstractItemModel;

class QtCheckHeaderView: public QHeaderView
{
    Q_OBJECT

public:
    explicit QtCheckHeaderView(Qt::Orientation orientation, QWidget *parent = 0);
    virtual ~QtCheckHeaderView();

    QList<int> checkableIndexes() const
    {
        return mCheckableIndexes;
    }

    bool addCheckable(int logicalIndex)
    {
        if (model() && !mCheckableIndexes.contains(logicalIndex))
        {
            mCheckableIndexes.append(logicalIndex);
            mCheckStates.insert(logicalIndex, Qt::Unchecked);
            updateCheckbox(logicalIndex);
            return true;
        }
        return false;
    }

    void removeCheckable(int logicalIndex)
    {
        mCheckableIndexes.removeOne(logicalIndex);
        mCheckStates.remove(logicalIndex);
    }

    void setModel(QAbstractItemModel* model);

protected slots:
    virtual void dataChanged(const QModelIndex & topLeft, const QModelIndex & bottomRight);

protected:
    void mousePressEvent(QMouseEvent* event);
    void paintSection(QPainter* painter, const QRect& rect, int logicalIndex) const;

    QList<int> mCheckableIndexes;
    QMap<int, Qt::CheckState> mCheckStates;
    bool blockDataChanged;
    mutable QMap<int, QRect> mSectionRects;

    void updateCheckbox(int logicalIndex);
    void updateModel(int logicalIndex);

    QRect checkRect(const QStyleOptionHeader& option, const QRect& bounding) const;

    inline bool rowIntersectsSelection(int row) const
    {
        return (selectionModel() ? selectionModel()->rowIntersectsSelection(row, rootIndex()) : false);
    }

    inline bool columnIntersectsSelection(int column) const
    {
        return (selectionModel() ? selectionModel()->columnIntersectsSelection(column, rootIndex()) : false);
    }

    inline bool sectionIntersectsSelection(int logical) const
    {
        return (orientation() == Qt::Horizontal ? columnIntersectsSelection(logical) : rowIntersectsSelection(
                                                      logical));
    }

    inline bool isRowSelected(int row) const
    {
        return (selectionModel() ? selectionModel()->isRowSelected(row, rootIndex()) : false);
    }

    inline bool isColumnSelected(int column) const
    {
        return (selectionModel() ? selectionModel()->isColumnSelected(column, rootIndex()) : false);
    }
};

#endif // QTCHECKHEADERVIEW_H
