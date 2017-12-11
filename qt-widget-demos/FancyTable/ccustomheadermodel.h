#ifndef CCUSTOMHEADERMODEL_H
#define CCUSTOMHEADERMODEL_H

#include <QStandardItemModel>

struct sSpan
{
    sSpan(){row = -1; col = -1; numRows = -1; numCols = -1; top = -1; left = -1; mValid = false; }
    sSpan(int r, int c, int nr, int nc, int t, int l) { row = r; col = c; numRows = nr; numCols = nc; top = t; left = l; mValid = true; }
    bool isValid() { return mValid; }
    int row;
    int col;
    int numRows;
    int numCols;
    int top;
    int left;
    bool mValid;
};

class cCustomHeaderModel : public QStandardItemModel
{
    Q_OBJECT

public:
    explicit cCustomHeaderModel(QObject *parent = 0);
    explicit cCustomHeaderModel(int, int, QObject *parent = 0);

    void setSpan(int row, int column, int rowSpanCount, int columnSpanCount);
    const sSpan & getSpan(int row, int column);

    QList<sSpan> & rowSpanList();
    QList<sSpan> & colSpanList();

private:
    sSpan m_InvalidSpan;
    QList<sSpan> m_SpanList;
};

#endif // CCUSTOMHEADERMODEL_H
