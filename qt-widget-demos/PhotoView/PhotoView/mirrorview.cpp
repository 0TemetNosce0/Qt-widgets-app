#include "mirrorview.h"

void MirrorView::setImageList(QList<int> imageList)
{
    items.clear();
    itemIndexList = imageList;
    currentIndex = 0;
    dIndex = 0;
}

void MirrorView::loadImage(int index,QPixmap image)
{
    if(itemIndexList.contains(index))
    {
        int currIndex = itemIndexList.at(currentIndex+dIndex);
        if(itemIndexList.indexOf(currIndex) < itemIndexList.indexOf(index)
            || items.count() == 0)//adding to the left side
            {
            MirroredItem* item = new MirroredItem(image,itemW,itemH);
            items << item;
            ui.graphicsView->scene()->addItem(item);
            item->setPos(lastX,lastY);
            item->setScatk(-1);
            item->moveTo(lastX,lastY);
            item->setZValue(lastX*-1);
        }
        else //addint to the right side
        {
            MirroredItem* item = new MirroredItem(image,itemW,itemH);
            int x,y;
            x = items.first()->getWX() + 50;
            y = items.first()->getWY() + 15;
            items.push_front(item);
            ui.graphicsView->scene()->addItem(item);
            item->setPos(x,y);
            item->setScatk(1);
            item->moveTo(x,y);
            item->setZValue(x);
            ++currentIndex;
            --dIndex;
            if(currentIndex < items.count() - 7)
            {
                ui.graphicsView->scene()->removeItem(items.last());
                MirroredItem* temp = items.takeLast();
                delete temp;
            }
        }
    }
}

void MirrorView::removeIndex(int index)
{
    if(itemIndexList.contains(index))
        itemIndexList.removeAt(itemIndexList.indexOf(index));
}

void MirrorView::resizeEvent(QResizeEvent*)
{
    makeScene();
    timer->start();
}

void MirrorView::showEvent(QShowEvent*)
{
    makeScene();
    timer->start();
}

void MirrorView::keyPressEvent(QKeyEvent* event)
{
    if(event->key() == Qt::Key_Left)
    {
        moveLeft();
    }
    else if(event->key() == Qt::Key_Right)
        moveRight();
    else if(event->key() == Qt::Key_Escape)
        emit hideMe();
}

void MirrorView::makeScene()
{
    QGraphicsScene* scene = new QGraphicsScene(0,0,ui.graphicsView->width()-10,
                                               ui.graphicsView->height()-10);
    QLinearGradient gradient(0,0,0,ui.graphicsView->height());
    gradient.setColorAt(0.0f,QColor(9,66,94));
    gradient.setColorAt(0.2f,QColor(3,77,94));
    gradient.setColorAt(0.45f,QColor(112,164,173));
    gradient.setColorAt(0.46f,QColor(0,15,15));
    gradient.setColorAt(1.0f,QColor(0,15,15));
    scene->setBackgroundBrush(QBrush(gradient));
    ui.graphicsView->setScene(scene);

    if(items.count() < currentIndex || currentIndex == -1)
        return;
    int centralX = static_cast<int>(scene->width()*0.5f
                                    - items[currentIndex]->getWidth()*0.5f);
    int centralY = static_cast<int>(scene->height()*0.5
                                    - items[currentIndex]->getHeight()*0.45f);
    for(int i = 0; i < items.count(); ++i)
        items[i]->setPos(centralX,centralY);

    //left items
    int leftPos = centralX - items[currentIndex]->getWidth() - 50;
    int leftPosY = centralY + 25;
    for(int i = currentIndex + 1; i < items.count(); ++i)
    {
        items[i]->setScatk(-1);
        items[i]->moveTo(leftPos,leftPosY);
        items[i]->setZValue(i);
        leftPos -= 50;
        leftPosY += 15;
        scene->addItem(items[i]);
    }
    lastX = leftPos + 50;
    lastY = leftPosY - 15;

    //center item
    items[currentIndex]->setScatk(0);
    items[currentIndex]->moveTo(centralX,centralY);
    items[currentIndex]->setZValue(0);
    scene->addItem(items[currentIndex]);

    //right items
    int rightPos = centralX + items[currentIndex]->getWidth() + 50;
    int rightPosY = centralY + 25;
    for(int i = currentIndex -1; i > -1; --i)
    {
        items[i]->setScatk(1);
        items[i]->moveTo(rightPos,rightPosY);
        items[i]->setZValue(i*-1);
        rightPos += 50;
        rightPosY += 15;
        scene->addItem(items[i]);
    }
}

void MirrorView::removeRight()
{
    dIndex += 15;
    currentIndex -= 15;
    for(int i = 0; i < 15; ++i)
        ui.graphicsView->scene()->removeItem(items.at(i));
    for(int i = 0; i < 15; ++i)
    {
        MirroredItem* item = items.takeFirst();
        delete item;
    }
}

void MirrorView::moveLeft()
{
    if((!timer->isActive()) && currentIndex - 1 >= 0)
    {
        --currentIndex;
        for(int i  = 0; i < items.count(); ++i)
        {
            if(i == currentIndex)
            {
                items[i]->moveCenter();
                items[i]->setScatk(0);
            }
            else if(i == currentIndex + 1)
            {
                items[i]->moveLeft();
                items[i]->setScatk(-1);
            }
            else
            {
                items[i]->moveLeft();
            }
        }
        if(dIndex > 0) //front chopped
        {
            if(currentIndex - 8 <=0)
                emit neededPhoto(itemIndexList.at(dIndex-1));
        }
        timer->start();
    }
}

void MirrorView::moveRight()
{
    if((!timer->isActive()) && currentIndex + 1 < items.count())
    {
        ++currentIndex;
        for(int i  = 0; i < items.count(); ++i)
        {
            if(i == currentIndex)
            {
                items[i]->moveCenter();
                items[i]->setScatk(0);
            }
            else if(i == currentIndex - 1)
            {
                items[i]->moveRight();
                items[i]->setScatk(1);
            }
            else
            {
                items[i]->moveRight();
            }
        }
        if(currentIndex > 25)
            removeRight();
        if(currentIndex + dIndex + 7 < itemIndexList.count()
            && currentIndex + 7 > items.count())
            emit neededPhoto(itemIndexList.at(currentIndex + dIndex + 7));
        timer->start();
    }
}

void MirrorView::animate()
{
    for(int i = 0; i < items.count(); ++i)
        items[i]->animate();
    bool stop = true;
    for(int i = 0; i < items.count(); ++i)
    {
        if(!items.at(i)->isInPlace())
        {
            stop = false;
            break;
        }
    }
    if(stop)
        timer->stop();
}

MirrorView::MirrorView(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    ui.graphicsView->setScene(new QGraphicsScene());
    QDesktopWidget desktop;
    itemW = static_cast<int>(desktop.width()*0.5f);
    itemH = desktop.height();
    currentIndex = 0;
    dIndex = 0;
    lastX = 0;
    lastY = 0;
    timer = new QTimer(this);
    timer->setInterval(20);
    ui.graphicsView->setFocusPolicy(Qt::NoFocus);
    connect(timer,SIGNAL(timeout()),this,SLOT(animate()));
}

MirrorView::~MirrorView()
{
}
