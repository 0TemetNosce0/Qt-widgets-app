#include "donut.h"

#include <qevent.h>

#include <QRect>
#include <QDebug>
#include <QPoint>
#include <QRegion>
#include <QBitmap>
#include <QPainter>
#include <QSharedPointer>


class Donut::Impl
{
public:
    Impl(const QPoint &pos, float iR, float oR)
        : m_innerRadius(iR)
        , m_outerRadius(oR)
        , m_pos(pos)
    {

    }

    ~Impl()
    {

    }

    void createMaskImage(QImage&);

    void drawDonut(QPainter&);
    void drawMask(QPainter&);

    float m_innerRadius;
    float m_outerRadius;
    QSharedPointer<QRegion> m_region;
    QSharedPointer<QRegion> m_innerRegion;
    QPoint m_pos;
    QRect m_rect;
    QImage m_maskImage;

private:
    Q_DISABLE_COPY(Impl)
};

void Donut::Impl::createMaskImage(QImage &image)
{
    int outerWidth = m_outerRadius * 2;
    int outerHeight = outerWidth;
    int innerWidth = m_innerRadius * 2;
    int innerHeight = m_innerRadius * 2;
    int widthDelta = (outerWidth - innerWidth) / 2;
    int heightDelta = (outerHeight - innerHeight) / 2;

    image = QImage(outerWidth, outerHeight, QImage::Format_ARGB32);
    image.fill(Qt::white);

    QPainter imagePainter(&image);

    imagePainter.setRenderHints(QPainter::Antialiasing);
    imagePainter.setPen(QPen(Qt::NoPen));
    imagePainter.setBrush(QColor(0, 0, 0));
    imagePainter.drawEllipse(0, 0, outerWidth, outerHeight);
    imagePainter.setBrush(Qt::white);
    imagePainter.drawEllipse(widthDelta, heightDelta, innerWidth, innerHeight);
}

void Donut::Impl::drawDonut(QPainter &painter)
{
#if (0)
    QRegion region = *region_ - *innerRegion_;
    setMask(region);
#else
    QBitmap bitmap = QBitmap::fromImage(m_maskImage, Qt::ColorOnly);
    //setMask(bitmap);
#endif

    int w = m_outerRadius * 2;
    int h = m_outerRadius * 2;

#if (1)
    QColor color(143, 143, 143);
    painter.setRenderHints(QPainter::SmoothPixmapTransform | QPainter::Antialiasing);
    painter.setPen(QPen(color));
    painter.setBrush(color);
    painter.drawRect(1, 1, w - 2, h - 2);

    painter.setBrush(color);
    QPainter::CompositionMode mode = painter.compositionMode();
    painter.setCompositionMode(QPainter::CompositionMode_Xor);
    int iW = m_innerRadius * 2;
    int iH = iW;
    int iX = (w - iW) / 2;
    int iY = iX;
    painter.drawRect(iX, iY, iW, iH);
    painter.setCompositionMode(mode);
    painter.setBrush(Qt::NoBrush);
    painter.setPen(QPen(color, 2));
    painter.drawRect(iX, iY, iW, iH);
#else
    painter.setRenderHints(QPainter::SmoothPixmapTransform | QPainter::Antialiasing);
    painter.drawImage(QRect(0, 0, w, h), bg_, QRect(0, 0, 117, 116));
    painter.setBrush(Qt::NoBrush);
    painter.setPen(QPen(Qt::black));
    painter.drawEllipse(1, 1, w-1, h-1);
#endif
}

void Donut::Impl::drawMask(QPainter &painter)
{
    painter.drawImage(0, 0, m_maskImage);
}

Donut::Donut(const QPoint &pos, float iR, float oR, QFrame *parent)
    : QFrame(parent)
    , d(new Impl(pos, iR, oR))

{
    int w = oR*2;
    int h = oR*2;
    int x = 0;//w/2;
    int y = 0;//h/2;

    int iW = iR * 2;
    int iH = iR * 2;
    int iX = x + (w - iW) / 2;
    int iY = y + (h - iH) / 2;

    d->m_region = QSharedPointer<QRegion>(new QRegion(x, y, w - 1, h - 1, QRegion::Ellipse));
    d->m_innerRegion = QSharedPointer<QRegion>(new QRegion(iX, iY, iW - 1, iH - 1, QRegion::Ellipse));
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
    setWindowModality(Qt::ApplicationModal);
    setAttribute(Qt::WA_TranslucentBackground);

    setGeometry(x + 100, y + 100, w, h);

    d->createMaskImage(d->m_maskImage);
}

Donut::~Donut()
{
}

QSize Donut::sizeHint() const
{
    int w = d->m_outerRadius * 2;
    int h = d->m_outerRadius * 2;

    return QSize(w, h);
}

void Donut::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

#if (1)
    d->drawDonut(painter);
#else
    d_->drawMask(painter);
#endif
}

void Donut::mousePressEvent(QMouseEvent *e)
{
    d->m_pos = e->screenPos().toPoint();
    d->m_rect = geometry();
}

void Donut::mouseMoveEvent(QMouseEvent *e)
{
    QPoint pos = e->screenPos().toPoint();
    int dx = pos.x() - d->m_pos.x();
    int dy = pos.y() - d->m_pos.y();
    QRect r = d->m_rect.adjusted(dx, dy, dx, dy);

    setGeometry(r);
}
