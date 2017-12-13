#ifndef GLOWEFFECT_H
#define GLOWEFFECT_H

#include <QGraphicsEffect>

extern void qt_blurImage(QImage &blurImage, qreal radius, bool quality, int transposed = 0);

class GlowEffect : public QGraphicsEffect
{
    Q_OBJECT
public:
    explicit GlowEffect(QObject *parent = 0);
    void setRadius(int radius);
    void setGlowColor(const QColor &color);
    QRectF boundingRectFor(const QRectF &sourceRect) const;

private:
    int radius;
    QColor color;

protected:
    void draw(QPainter *painter);
    void sourceChanged(ChangeFlags flags);
    
};

#endif // GLOWEFFECT_H
