#include "crect.h"

cRect::cRect()
    : mRow(-1)
    , mCol(-1)
    , mRect(QRect())
{

}

cRect::cRect(int row, int col, QRect rect)
    : mRow(row)
    , mCol(col)
    , mRect(rect)
{

}
