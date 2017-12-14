#ifndef CRECT_H
#define CRECT_H

#include <QRect>

class cRect
{
public:
    cRect();
    cRect(int row, int col, QRect rect);
    int mRow;
    int mCol;
    QRect mRect;
};

#endif // CRECT_H
