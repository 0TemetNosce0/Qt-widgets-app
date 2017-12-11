#ifndef HIERARCHICAL_HEADER_VIEW_H
#define HIERARCHICAL_HEADER_VIEW_H

#include <QHeaderView>

class HierarchicalHeaderView : public QHeaderView
{
    Q_OBJECT

    class private_data;
    private_data* m_pd;

    QStyleOptionHeader styleOptionForCell(int logicalIndex) const;

protected:
    void paintSection(QPainter* painter, const QRect& rect, int logicalIndex) const;
    QSize sectionSizeFromContents(int logicalIndex) const;

public:

    enum HeaderDataModelRoles
    {
        HorizontalHeaderDataRole = Qt::UserRole,
        VerticalHeaderDataRole = Qt::UserRole + 1
    };

    HierarchicalHeaderView(Qt::Orientation orientation, QWidget* parent = 0);
    ~HierarchicalHeaderView();

    void setModel(QAbstractItemModel* model);

private slots:
    void on_sectionResized(int logicalIndex);
};

#endif
