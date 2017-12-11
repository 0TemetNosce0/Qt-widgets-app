#include "graphicsbezieritem.h"

#include <cassert>
#include <QPainter>
#include <QDebug>

const float GraphicsBezierItem::DEFAULT_PRECISION = 0.05f;

GraphicsBezierItem::GraphicsBezierItem(QGraphicsItem *parent) :
    QGraphicsItem(/*QPointF(0,0), QPointF(0,0), */parent) {
}

GraphicsBezierItem::GraphicsBezierItem(const QPointF &c1, const QPointF &c2,
                                       float precision, QGraphicsItem *parent)
    : QGraphicsItem(parent)
    , precision(precision)
{
    controls.push_back(c1);
    controls.push_back(c2);
    update();
}

void GraphicsBezierItem::addControl(const QPointF &c) {
    controls.insert(controls.end()--, c);
    update();
}

void GraphicsBezierItem::removeControl(std::size_t num) {
    std::size_t size = controls.size();

    if (size <= 2)
        throw std::logic_error("Bezier curve must contain at least 2 control points");

    assert(num < size);
    controls.erase(controls.begin() + num);
    update();
}

void GraphicsBezierItem::setControl(std::size_t num, const QPointF &c) {
    assert(num < controls.size());
    controls[num] = c;
    update();
}

const std::vector<QPointF>& GraphicsBezierItem::getControls() const {
    return controls;
}

const std::vector<QPointF>& GraphicsBezierItem::getCurve() const {
    return curve;
}

float GraphicsBezierItem::getPrecision() const {
    return precision;
}

void GraphicsBezierItem::setPrecision(float value) {
    precision = value;
}

QPen GraphicsBezierItem::getPen() const {
    return pen;
}

void GraphicsBezierItem::setPen(const QPen &value) {
    pen = value;
    updateRect();
}

QRectF GraphicsBezierItem::boundingRect() const {
    return rect;
}

void GraphicsBezierItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(pen);
    painter->drawPolyline(curve.data(), curve.size());
}

void GraphicsBezierItem::update() {
    curve.clear();

    for (float t = 0.f ; t <= 1.f ; t += precision)
        curve.push_back(tCurve(controls, t));

    updateRect();
}

void GraphicsBezierItem::updateRect() {
    rect.setRect(0,0,0,0);

    for (int i = 0; i < curve.size(); ++i)
    {
        QPointF p = curve.at(i);
        if (p.x() <= rect.left())
            rect.setLeft(p.x());
        else if (p.x() >= rect.right())
            rect.setRight(p.x());

        if (p.y() <= rect.top())
            rect.setTop(p.y());
        else if (p.y() >= rect.bottom())
            rect.setBottom(p.y());
    }
}

QPointF GraphicsBezierItem::tCurve(std::vector<QPointF> points, float t) {
    std::vector<QPointF> npoints;
    std::size_t size = points.size();

    if (size == 1)
        return points[0];
    else {
        for (std::size_t i = 0 ; i < size - 1 ; i++)
            npoints.push_back((points[i+1] - points[i]) * t + points[i]);

        return tCurve(npoints, t);
    }
}




