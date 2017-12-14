#include <QApplication>
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QGraphicsView>

#include "controlitem.h"
#include "graphicsbezieritem.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QGraphicsScene scene;
    scene.setSceneRect(0, 0, 400, 400);

    GraphicsBezierItem *gbi = new GraphicsBezierItem(QPointF(50,50), QPointF(350,50), 0.05f);
    gbi->addControl(QPointF(200,200));
    scene.addItem(gbi);

    QGraphicsView view(&scene);
    view.setRenderHints(QPainter::Antialiasing);
    view.show();

    return app.exec();
}
