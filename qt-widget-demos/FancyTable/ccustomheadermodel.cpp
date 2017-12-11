#include "ccustomheadermodel.h"
#include <QDebug>

cCustomHeaderModel::cCustomHeaderModel(QObject *parent) 
    : QStandardItemModel(parent)
{

}

cCustomHeaderModel::cCustomHeaderModel(int rows, int cols, QObject *parent) 
    : QStandardItemModel(rows, cols, parent)
{

}

// firstRow: coordinate where the row span starts
// firstColumn: coordinate where the column span start
// numRows: number of row cells spanned
// numCols: number of column cells spanned
void cCustomHeaderModel::setSpan(int firstRow, int firstColumn, int numRows, int numCols)
{
    for(int r = firstRow; r < firstRow + numRows; ++r)
    {
        for(int c = firstColumn; c < firstColumn + numCols; ++c)
        {
            m_SpanList.append(sSpan(r, c, numRows, numCols, firstRow, firstColumn));
        }
    }
}

const sSpan &cCustomHeaderModel::getSpan(int row, int column)
{
    for(QList<sSpan>::const_iterator it = m_SpanList.begin(); it != m_SpanList.end(); ++it)
    {
        if((*it).row == row && (*it).col == column)
        {
            return *it;
        }
    }

    return m_InvalidSpan;
}
