#include "regionImage.h"

RegionImage::RegionImage(float iR, float oR)
{
    int w = 2 * oR;
    int h = 2 * oR;
    image_ = QImage(QSize(w, h), QImage::Format_ARGB32);
}
