#ifndef DIAGTABLEHEADER_H
#define DIAGTABLEHEADER_H

#include <QHeaderView>

class DiagTableHeader : public QHeaderView
{
    Q_OBJECT
public:
    DiagTableHeader(QWidget* parent = 0);
    virtual ~DiagTableHeader(){}

    int sectionSizeHint(int logicalIndex) const;
    QSize sizeHint() const;

private:
    virtual void paintSection(QPainter* painter, const QRect& rect, int logicalIndex) const;
};

#endif // DIAGTABLEHEADER_H
