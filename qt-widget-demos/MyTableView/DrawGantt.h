#ifndef DRAWGANNT_H
#define DRAWGANNT_H

#include <QObject>
#include <QPainter>

class DrawGantt : public QObject
{
    Q_OBJECT

public:
    DrawGantt();
    void paintCell(QPainter *painter, const QRect &rect, int row);

private:
};

#endif
