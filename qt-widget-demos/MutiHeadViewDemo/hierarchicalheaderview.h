#ifndef HIERARCHICAL_HEADER_VIEW_H
#define HIERARCHICAL_HEADER_VIEW_H

#include <QHeaderView>

class HierarchicalHeaderView : public QHeaderView
{
    Q_OBJECT

public:
    enum HeaderDataModelRoles
    {
        HorizontalHeaderDataRole = Qt::UserRole,
        VerticalHeaderDataRole = Qt::UserRole+1
    };

    HierarchicalHeaderView(Qt::Orientation orientation, QWidget* parent = 0);
    ~HierarchicalHeaderView();

    void setModel(QAbstractItemModel* model);

protected:
    void paintSection(QPainter* painter, const QRect& rect, int logicalIndex) const;
    QSize sectionSizeFromContents(int logicalIndex) const;

private slots:
    void on_sectionResized(int logicalIndex);

private:
    class private_data;
    private_data* _pd;

    QStyleOptionHeader styleOptionForCell(int logicalIndex) const;
};

#endif
