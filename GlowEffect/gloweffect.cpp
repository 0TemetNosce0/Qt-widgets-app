#include "gloweffect.h"
#include <qpainter.h>
#include <QPixmap>
#include <QDebug>

GlowEffect::GlowEffect(QObject *parent) :
    QGraphicsEffect(parent), radius(0), color(255, 255, 255, 255)
{
}

void GlowEffect::setRadius(int radius)
{
    this->radius = radius;
    updateBoundingRect();
    update();
}

void GlowEffect::setGlowColor(const QColor &color)
{
    this->color = color;
    update();
}

QRectF GlowEffect::boundingRectFor(const QRectF &sourceRect) const
{
    QRectF tmp(sourceRect);
    tmp.setBottomRight(tmp.bottomRight() + QPointF(radius * 2, radius * 2));
    return tmp;
}

void GlowEffect::draw(QPainter *painter)
{
    if (!radius)
    {
        drawSource(painter);//直接绘制，不处理
        return;
    }
    QPixmap source = sourcePixmap();//返回一个像素图
    QImage sourceBlured(source.size() + QSize(radius * 2, radius * 2), QImage::Format_ARGB32_Premultiplied);//qImage
    sourceBlured.fill(0);//QImage填充颜色
    QPainter tmpPainter(&sourceBlured);//在QImage上的画笔
    tmpPainter.drawPixmap(radius, radius, source);
    tmpPainter.setCompositionMode(QPainter::CompositionMode_SourceIn);
    tmpPainter.fillRect(sourceBlured.rect(), color);
    tmpPainter.end();

    qt_blurImage(sourceBlured, radius, true);//不知道

    painter->drawImage(0, 0, sourceBlured);
    painter->drawImage(0, 0, sourceBlured);////绘制sourceBlured
    painter->drawPixmap(radius, radius, source);//绘制source
}

void GlowEffect::sourceChanged(ChangeFlags flags)
{
    updateBoundingRect();
    update();//会调用draw绘制
}
