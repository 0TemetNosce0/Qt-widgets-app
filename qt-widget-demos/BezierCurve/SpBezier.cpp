#include "SpBezier.h"

using namespace std;


SpBezier::SpBezier(SpNode &a,SpNode &b)
{
    QPointF P1 = a.GetPosition(), P2 = b.GetPosition(), A1 = a.getLef()->GetPosition(), A2 = b.getRig()->GetPosition();

    A1.setX(A1.x()+P1.x()); A1.setY(A1.y()+P1.y());
    A2.setX(A2.x()+P2.x()); A2.setY(A2.y()+P2.y());

    curve.append(P1);
    curve.append(A1);
    curve.append(A2);
    curve.append(P2);

    genB();
}

void SpBezier::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHint(QPainter::Antialiasing);

    painter->setBrush(Qt::black);
    QPointF *cp;
    cp = new QPointF[curve.size()];

    for(int i = 0; i < curve.size(); i++)
    {
        cp[i] = curve[i];
    }

    painter->drawPolyline(cp, curve.size());

}

QList<QPointF> teile(QList<QPointF> list, int index)
{
    QPointF tmp;

    list.insert(index+3, tmp); list.insert(index+2, tmp); list.insert(index+1, tmp);
    list[index+1].setX(0.5*list[index].x()+0.5*list[index+2].x()); list[index+1].setY(0.5*list[index].y()+0.5*list[index+2].y());
    list[index+5].setX(0.5*list[index+4].x()+0.5*list[index+6].x()); list[index+5].setY(0.5*list[index+4].y()+0.5*list[index+6].y());
    list[index+3].setX(0.5*list[index+2].x()+0.5*list[index+4].x()); list[index+3].setY(0.5*list[index+2].y()+0.5*list[index+4].y());
    list[index+2].setX(0.5*list[index+1].x()+0.5*list[index+3].x()); list[index+2].setY(0.5*list[index+1].y()+0.5*list[index+3].y());
    list[index+4].setX(0.5*list[index+3].x()+0.5*list[index+5].x()); list[index+4].setY(0.5*list[index+3].y()+0.5*list[index+5].y());
    list[index+3].setX(0.5*list[index+2].x()+0.5*list[index+4].x()); list[index+3].setY(0.5*list[index+2].y()+0.5*list[index+4].y());

    return list;
}

void SpBezier::genB()
{
    curve = teile(curve, 0);
    curve = teile(curve, 3);
    curve = teile(curve, 0);
    curve = teile(curve, 9);
    curve = teile(curve, 6);
    curve = teile(curve, 3);
    curve = teile(curve, 0);
    curve = teile(curve, 21);
    curve = teile(curve, 18);
    curve = teile(curve, 15);
    curve = teile(curve, 12);
    curve = teile(curve, 9);
    curve = teile(curve, 6);
    curve = teile(curve, 3);
    curve = teile(curve, 0);
}

