#include "adgraphicsview.h"

AdGraphicsView::AdGraphicsView()
{

}

AdGraphicsView::~AdGraphicsView()
{

}

void AdGraphicsView::loadMap(QByteArray map)
{
    this->adMap.loadFromData(map);
}

void AdGraphicsView::init()
{
    width = this->adMap.width();
    height = this->adMap.height();
    QLabel *cornerLabel = new QLabel(QStringLiteral("¹ã¸æ"));

    adScene = new QGraphicsScene(this);

    adScene->setSceneRect(-width/2, -height/2, width, height);

    this->setScene(adScene);
    this->setCacheMode(CacheBackground);

    QVBoxLayout *advLayout = new QVBoxLayout;
    advLayout->addWidget(cornerLabel);
    advLayout->setMargin(15);
    advLayout->addStretch();

    QHBoxLayout *adhLayout = new QHBoxLayout;
    adhLayout->addLayout(advLayout);
    adhLayout->addStretch();
    adhLayout->setDirection(QBoxLayout::RightToLeft);

    this->setLayout(adhLayout);
}

void AdGraphicsView::viewUpdate()
{
    width = this->adMap.width();
    height = this->adMap.height();
    this->adScene->setSceneRect(-width/2, -height/2, width, height);
    this->repaint();
}

void AdGraphicsView::drawBackground(QPainter *painter, const QRectF &rect)
{
    painter->drawPixmap(int(sceneRect().left()),int(sceneRect().top()),this->adMap);
}
