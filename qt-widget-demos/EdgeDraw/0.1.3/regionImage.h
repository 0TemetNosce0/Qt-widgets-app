#ifndef REGIONIMAGE_H
#define REGIONIMAGE_H

#include <QImage>

class QColor;

class RegionImage
{
public:
    RegionImage(float iR, float oR);
    void setColor(const QColor&);

private:
    QImage image_;
};

#endif // REGIONIMAGE_H
