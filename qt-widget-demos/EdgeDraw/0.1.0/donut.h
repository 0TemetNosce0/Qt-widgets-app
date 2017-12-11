#ifndef DONUT_H
#define DONUT_H

#include <QFrame>
#include <QScopedPointer>

class QRegion;

class Donut : public QFrame
{
public:
    Donut(const QPoint &pos, float iR, float oR, QFrame *parent = nullptr);
    virtual ~Donut();

protected:
    virtual QSize sizeHint() const;
    virtual void paintEvent(QPaintEvent *);
    virtual void mousePressEvent(QMouseEvent *);
    virtual void mouseMoveEvent(QMouseEvent *);

private:
    class Impl;

    QScopedPointer<Impl> d;
};

#endif // DONUT_H
